/************************************************************************\

  Low bitrate LPC CODEC derived from the public domain implementation 
  of Ron Frederick.
  
  The basic design is preserved, except for several bug fixes and
  the following modifications:
    
  1. The pitch detector operates on the (downsampled) signal, not on 
  the residue. This appears to yield better performances, and it
  lowers the processing load.
  2. Each frame is elongated by 50% prefixing it with the last half
  of the previous frame. This design, inherited from the original
  code for windowing purposes, is exploited in order to provide 
  two independent pitch analyses: on the first 2/3, and on the 
  second 2/3 of the elongated frame (of course, they overlap by 
  half):
      
  last half old frame	            new frame
  --------------------========================================
  <--------- first pitch region --------->
                      <--------- second pitch region  ------->
        
  Two voiced/unvoiced flags define the voicing status of each
  region; only one value for the period is retained (if both
  halves are voiced, the average is used).
  The two flags are used by the synthesizer for the halves of
  each frame to play back. Of course, this is non optimal but
  is good enough (a half-frame would be too short for measuring
  low pitches)
  3. The parameters (one float for the period (pitch), one for the
  gain, and ten for the LPC-10 filter) are quantized according 
  this procedure:
  - the period is logarithmically compressed, then quantized 
  as 8-bit unsigned int (6 would actually suffice)
  - the gain is logarithmically compressed (using a different
  formula), then quantized at 6-bit unsigned int. The two
  remaining bits are used for the voicing flags.
  - the first two LPC parameters (k[1] and k[2]) are multiplied
  by PI/2, and the arcsine of the result is quantized as
  6 and 5 bit signed integers. This has proved more effective
  than the log-area compression used by LPC-10.
  - the remaining eight LPC parameters (k[3]...k[10]) are
  quantized as, respectively, 5,4,4,3,3,3,3 and 2 bit signed
  integers.
  Finally, period and gain plus voicing flags are stored in the
  first two bytes of the 7-byte parameters block, and the quantized
  LPC parameters are packed into the remaining 5 bytes. Two bits
  remain unassigned, and can be used for error detection or other
  purposes.

  The frame lenght is actually variable, and is simply passed as 
  initialization parameter to lpc_init(): this allows to experiment
  with various frame lengths. Long frames reduce the bitrate, but
  exceeding 320 samples (i.e. 40 ms, at 8000 samples/s) tend to
  deteriorate the speech, that sounds like spoken by a person 
  affected by a stroke: the LPC parameters (modeling the vocal 
  tract) can't change fast enough for a natural-sounding synthesis.
  25 ms per frame already yields a quite tight compression, corresponding
  to 1000/40 * 7 * 8 = 1400 bps. The quality improves little with 
  frames shorter than 250 samples (32 frames/s), so this is a recommended
  compromise. The bitrate is 32 * 7 * 8 = 1792 bps.
  
  The synthesizer has been modified as well. For voiced subframes it 
  now uses a sawtooth excitation, instead of the original pulse train.
  This idea, copied from MELP, reduces the buzzing-noise artifacts.
  In order to compensate the non-white spectrum of the sawtooth, a 
  pre-emphasis is applied to the signal before the Durbin calculation.
  The filter has (in s-space) two zeroes at (640, 0) Hz and two poles 
  at (3200, 0) Hz. These filters have been handoded, and may not be 
  optimal. Two other filters (anti-hum high-pass with corner at 100 Hz,
  and pre-downsampling lowpass with corner at 300 Hz) are Butterworth
  designs produced by the MkFilter package by A.J. Fisher
  (http://www.cs.york.ac.uk/~fisher/mkfilter/).

  The C style has been ANSI-fied.

  Complexity: As any LPC CODEC, also this one is not very demanding:
  for real-time use analysis and synthesis takes each about 6 - 8% 
  of the CPU cycles on a Cy686/166, when the code is compiled with 
  MSVC++ 4.2 with /Ox or gcc with -O3.
  However, a floating point unit is absolutely required.


\************************************************************************/

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>							   

#include "soundpipe.h"
#include "openlpc.h"
#include "ftol.h"

#define PREEMPH

#define bcopy(a, b, n)	  memmove(b, a, n)

#ifndef M_PI
#define M_PI (3.1415926535897932384626433832795)
#endif

static float my_fs = 11025.0;
#define LPC_FILTORDER		10
#define FS		my_fs /* Sampling rate */
#define MAXWINDOW	1000	/* Max analysis window length */

typedef struct openlpc_e_state{
	float   s[MAXWINDOW], y[MAXWINDOW], h[MAXWINDOW];
    int     framelen, buflen;
    float   xv1[3], yv1[3], 
            xv2[2], yv2[2], 
			xv3[1], yv3[3], 
			xv4[2], yv4[2];
    float   w[MAXWINDOW], r[LPC_FILTORDER+1];
} openlpc_e_state_t;

typedef struct openlpc_d_state{
		float Oldper, OldG, Oldk[LPC_FILTORDER + 1];
        float bp[LPC_FILTORDER+1];
        float exc;
		int pitchctr, framelen, buflen;
} openlpc_d_state_t;

#define FC		200.0	/* Pitch analyzer filter cutoff */
#define DOWN		5	/* Decimation for pitch analyzer */
#define MINPIT		40.0	/* Minimum pitch (observed: 74) */
#define MAXPIT		320.0	/* Maximum pitch (observed: 250) */

#define MINPER		(int)(FS/(DOWN*MAXPIT)+.5)	/* Minimum period  */
#define MAXPER		(int)(FS/(DOWN*MINPIT)+.5)	/* Maximum period  */

#define REAL_MINPER	 (DOWN*MINPER) /* converted to samples units */

#define WSCALE		1.5863	/* Energy loss due to windowing */

#define BITS_FOR_LPC 38

#define ARCSIN_Q /* provides better quantization of first two k[] at low bitrates */

#if BITS_FOR_LPC == 38
/* (38 bit LPC-10, 2.7 Kbit/s @ 20ms, 2.4 Kbit/s @ 22.5 ms */
static int parambits[LPC_FILTORDER] = {6,5,5,4,4,3,3,3,3,2};
#elif BITS_FOR_LPC == 32
/* (32 bit LPC-10, 2.4 Kbit/s, not so good */
static int parambits[LPC_FILTORDER] = {5,5,5,4,3,3,2,2,2,1};
#else /* BITS_FOR_LPC == 80	*/
/* 80-bit LPC10, 4.8 Kbit/s */
static int parambits[LPC_FILTORDER] = {8,8,8,8,8,8,8,8,8,8};
#endif

static float logmaxminper;
static int sizeofparm;	/* computed by lpc_init */

static void auto_correl1(float *w, int n, float *r)
{
    int i, k;
    
    for (k=0; k <= MAXPER; k++, n--) {
        r[k] = 0.0;
        for (i=0; i < n; i++) {
            r[k] += (w[i] *  w[i+k]);
        }
    }
}

static void auto_correl2(float *w, int n, float *r)
{
    int i, k;
    
    for (k=0; k <= LPC_FILTORDER; k++, n--) {
        r[k] = 0.0;
        for (i=0; i < n; i++) {
            r[k] += (w[i] *  w[i+k]);
        }
    }
}

static void durbin(float r[], int p, float k[], float *g)
{
    int i, j;
    float a[LPC_FILTORDER+1], at[LPC_FILTORDER+1], e;
    
    for (i=0; i <= p; i++) a[i] = at[i] = 0.0;
    
    e = r[0];
    for (i=1; i <= p; i++) {
        k[i] = -r[i];
        for (j=1; j < i; j++) {
            at[j] = a[j];
            k[i] -= a[j] * r[i-j];
        }
        if (e == 0) {  /* fix by John Walker */
            *g = 0;
            return;
        }
        k[i] /= e;
        a[i] = k[i];
        for (j=1; j < i; j++) a[j] = at[j] + k[i] * at[i-j];
        e *= 1.0f - k[i]*k[i];
    }
    if (e < 0) {
        e = 0; /* fix by John Walker */
    }
    *g = (float)sqrt(e);
}

/* Enzo's streamlined pitch extractor - on the signal, not the residue */

static void calc_pitch(float *w, int len, float *per)
{
    int i, j, rpos;
    float d[MAXWINDOW/DOWN], r[MAXPER+1], rmax;
    float rval, rm, rp;
    float x, y;
    float vthresh;

    /* decimation */
    for (i=0, j=0; i < len; i+=DOWN) 
        d[j++] = w[i];
    
    auto_correl1(d, len/DOWN, r); 
    
    /* find peak between MINPER and MAXPER */
    x = 1;
    rpos = 0;
    rmax = 0.0;
    y = 0;
    rm = 0;
    rp = 0;

    vthresh = 0.;
     
    for (i = 1; i < MAXPER; i++) {
        rm = r[i-1];
        rp = r[i+1];
        y = rm+r[i]+rp; /* find max of integral from i-1 to i+1 */
        
        if ((y > rmax) && (r[i] > rm) && (r[i] > rp) && (i > MINPER)) {
            rmax = y;
            rpos = i;
        }
    }
    
    /* consider adjacent values */
    rm = r[rpos-1];
    rp = r[rpos+1];
    
#if 0
    {
        float a, b, c, x, y;
        /* parabolic interpolation */
        a = 0.5f * rm - rmax + 0.5f * rp;
        b = -0.5f*rm*(2.0f*rpos+1.0f) + 2.0f*rpos*rmax + 0.5f*rp*(1.0f-2.0f*rpos);
        c = 0.5f*rm*(rpos*rpos+rpos) + rmax*(1.0f-rpos*rpos) + 0.5f*rp*(rpos*rpos-rpos);
        
        /* find max of interpolating parabole */
        x = -b / (2.0f * a);
        y = a*x*x + b*x + c;
        
        rmax = y;
        /* normalize, so that 0. < rval < 1. */ 
        rval = (r[0] == 0 ? 1.0f : rmax / r[0]);
    }
#else
    if(rpos > 0) {
        x = ((rpos-1)*rm + rpos*r[rpos] + (rpos+1)*rp)/(rm+r[rpos]+rp); 
    }
    /* normalize, so that 0. < rval < 1. */ 
    rval = (r[0] == 0 ? 0 : r[rpos] / r[0]);
#endif
    
    /* periods near the low boundary and at low volumes
    are usually spurious and 
    manifest themselves as annoying mosquito buzzes */
    
    *per = 0;	/* default: unvoiced */
    if ( x > MINPER &&  /* x could be < MINPER or even < 0 if pos == MINPER */
        x < (MAXPER+1) /* same story */
        ) {
        
        vthresh = 0.6f; 
        if(r[0] > 0.002)	   /* at low volumes (< 0.002), prefer unvoiced */ 
            vthresh = 0.25;       /* drop threshold at high volumes */
        
        if(rval > vthresh)
            *per = x * DOWN;
    }
}

/* Initialization of various parameters */

openlpc_encoder_state *create_openlpc_encoder_state(void)
{
    openlpc_encoder_state *state;
    
    state = (openlpc_encoder_state *)calloc(1, sizeof(openlpc_encoder_state));
    
    return state;
}


void init_openlpc_encoder_state(openlpc_encoder_state *st, int framelen)
{
    int i, j;
    
    st->framelen = framelen;
    
    st->buflen = framelen*3/2;
    /*  (st->buflen > MAXWINDOW) return -1;*/
    
    for(i=0, j=0; i<sizeof(parambits)/sizeof(parambits[0]); i++) {
        j += parambits[i];
    }
    sizeofparm = (j+7)/8 + 2;
    for (i = 0; i < st->buflen; i++) {
        st->s[i] = 0.0;
        st->h[i] = (float)(WSCALE*(0.54 - 0.46 * cos(2 * M_PI * i / (st->buflen-1.0))));
    }
    /* init the filters */
    st->xv1[0] = st->xv1[1] = st->xv1[2] = st->yv1[0] = st->yv1[1] = st->yv1[2] = 0.0f;
    st->xv2[0] = st->xv2[1] = st->yv2[0] = st->yv2[1] = 0.0f;
    st->xv3[0] = st->yv3[0] = st->yv3[1] = st->yv3[2] = 0.0f;
    st->xv4[0] = st->xv4[1] = st->yv4[0] = st->yv4[1] = 0.0f;
    
    logmaxminper = (float)log((float)MAXPER/MINPER);
    
}

void destroy_openlpc_encoder_state(openlpc_encoder_state *st)
{
    if(st != NULL)
    {
        free(st);
        st = NULL;
    }
}

/* LPC Analysis (compression) */

int openlpc_encode(const short *buf, unsigned char *parm, openlpc_encoder_state *st)
{
    int i, j;
    float per, gain, k[LPC_FILTORDER+1];
    float per1, per2;
    float xv10, xv11, xv12, yv10, yv11, yv12,
        xv20, xv21, yv20, yv21,
        xv30, yv30, yv31, yv32,
        xv40, xv41, yv40, yv41;
    
    xv10 = st->xv1[0];
    xv11 = st->xv1[1];
    xv12 = st->xv1[2];
    yv10 = st->yv1[0];
    yv11 = st->yv1[1];
    yv12 = st->yv1[2];
    xv30 = st->xv3[0];
    yv30 = st->yv3[0];
    yv31 = st->yv3[1];
    yv32 = st->yv3[2];
    for(i = 0; i < LPC_FILTORDER + 1; i++) k[i] = 0;
    /* convert short data in buf[] to signed lin. data in s[] and prefilter */
    for (i=0, j=st->buflen - st->framelen; i < st->framelen; i++, j++) {
        
        float u = (float)(buf[i]/32768.0f);
        
        /* Anti-hum 2nd order Butterworth high-pass, 100 Hz corner frequency */
        /* Digital filter designed by mkfilter/mkshape/gencode   A.J. Fisher
        mkfilter -Bu -Hp -o 2 -a 0.0125 -l -z */
        
        xv10 = xv11;
        xv11 = xv12; 
        xv12 = (float)(u * 0.94597831f); /* /GAIN */
        
        yv10 = yv11;
        yv11 = yv12; 
        yv12 = (float)((xv10 + xv12) - 2 * xv11
            + ( -0.8948742499f * yv10) + ( 1.8890389823f * yv11));
        
        u = st->s[j] = yv12;	/* also affects input of next stage, to the LPC filter synth */
        
        /* low-pass filter s[] -> y[] before computing pitch */
        /* second-order Butterworth low-pass filter, corner at 300 Hz */
        /* Digital filter designed by mkfilter/mkshape/gencode   A.J. Fisher
        MKFILTER.EXE -Bu -Lp -o 2 -a 0.0375 -l -z */
        
        /*st->xv3[0] = (float)(u / 2.127814584e+001);*/ /* GAIN */
        xv30 = (float)(u * 0.04699658f); /* GAIN */
        yv30 = yv31;
        yv31 = yv32; 
        yv32 = xv30 + (float)(( -0.7166152306f * yv30) + (1.6696186545f * yv31));
        st->y[j] = yv32;
    }
    st->xv1[0] = xv10;
    st->xv1[1] = xv11;
    st->xv1[2] = xv12;
    st->yv1[0] = yv10;
    st->yv1[1] = yv11;
    st->yv1[2] = yv12;
    st->xv3[0] = xv30;
    st->yv3[0] = yv30;
    st->yv3[1] = yv31;
    st->yv3[2] = yv32;
#ifdef PREEMPH
    /* operate optional preemphasis s[] -> s[] on the newly arrived frame */
    xv20 = st->xv2[0];
    xv21 = st->xv2[1];
    yv20 = st->yv2[0];
    yv21 = st->yv2[1];
    xv40 = st->xv4[0];
    xv41 = st->xv4[1];
    yv40 = st->yv4[0];
    yv41 = st->yv4[1];
    for (j=st->buflen - st->framelen; j < st->buflen; j++) {
        float u = st->s[j];
        
        /* handcoded filter: 1 zero at 640 Hz, 1 pole at 3200 */
#define TAU (FS/3200.f)
#define RHO (0.1f)
        xv20 = xv21; 	/* e(n-1) */
        xv21 = (float)(u * 1.584f);		/* e(n)	, add 4 dB to compensate attenuation */
        yv20 = yv21;
        yv21 = (float)(TAU/(1.f+RHO+TAU) * yv20 	 /* u(n) */
            + (RHO+TAU)/(1.f+RHO+TAU) * xv21
            - TAU/(1.f+RHO+TAU) * xv20);
        u = yv21;
        
        /* cascaded copy of handcoded filter: 1 zero at 640 Hz, 1 pole at 3200 */
        xv40 = xv41;
        xv41 = (float)(u * 1.584f);
        yv40 = yv41;
        yv41 = (float)(TAU/(1.f+RHO+TAU) * yv40
            + (RHO+TAU)/(1.f+RHO+TAU) * xv41
            - TAU/(1.f+RHO+TAU) * xv40);
        u = yv41;
        
        st->s[j] = u;
    }
    st->xv2[0] = xv20;
    st->xv2[1] = xv21;
    st->yv2[0] = yv20;
    st->yv2[1] = yv21;
    st->xv4[0] = xv40;
    st->xv4[1] = xv41;
    st->yv4[0] = yv40;
    st->yv4[1] = yv41;
#endif
    
    /* operate windowing s[] -> w[] */
    
    for (i=0; i < st->buflen; i++)
        st->w[i] = st->s[i] * st->h[i];
    
    /* compute LPC coeff. from autocorrelation (first 11 values) of windowed data */
    auto_correl2(st->w, st->buflen, st->r);
    durbin(st->r, LPC_FILTORDER, k, &gain);
    
    /* calculate pitch */
    calc_pitch(st->y, st->framelen, &per1);                 /* first 2/3 of buffer */
    calc_pitch(st->y + st->buflen - st->framelen, st->framelen, &per2); /* last 2/3 of buffer */
    if(per1 > 0 && per2 >0)
        per = (per1+per2)/2;
    else if(per1 > 0)
        per = per1;
    else if(per2 > 0)
        per = per2;
    else
        per = 0;
    
    /* logarithmic q.: 0 = MINPER, 256 = MAXPER */
    parm[0] = (unsigned char)(per == 0? 0 : (unsigned char)(log(per/(REAL_MINPER)) / logmaxminper * (1<<8)));
    
#ifdef LINEAR_G_Q
    i = gain * (1<<7);
    if(i > 255) 	/* bug fix by EM */
        i = 255;
#else
    i = (int)(float)(256.0f * log(1 + (2.718-1.f)/10.f*gain)); /* deriv = 5.82 allowing to reserve 2 bits */
    if(i > 255) i = 255;	 /* reached when gain = 10 */
    i = (i+2) & 0xfc;
#endif
    
    parm[1] = (unsigned char)i;
    
    if(per1 > 0)
        parm[1] |= 1;
    if(per2 > 0)
        parm[1] |= 2;
    
    for(j=2; j < sizeofparm; j++)
        parm[j] = 0;
    
    for (i=0; i < LPC_FILTORDER; i++) {
        int bitamount = parambits[i];
        int bitc8 = 8-bitamount;
        int q = (1 << bitc8);  /* quantum: 1, 2, 4... */
        float u = k[i+1];
        int iu;
#ifdef ARCSIN_Q
        if(i < 2) u = (float)(asin(u)*2.f/M_PI);
#endif
        u *= 127;
        if(u < 0)
            u += (0.6f * q);
        else
            u += (0.4f * q); /* highly empirical! */
        
        iu = lrintf(u);
        iu = iu & 0xff; /* keep only 8 bits */
        
        /* make room at the left of parm array shifting left */
        for(j=sizeofparm-1; j >= 3; j--) {
            parm[j] = (unsigned char)((parm[j] << bitamount) | (parm[j-1] >> bitc8));
        }
        parm[2] = (unsigned char)((parm[2] << bitamount) | (iu >> bitc8)); /* parm[2] */
    }
    
    bcopy(st->s + st->framelen, st->s, (st->buflen - st->framelen)*sizeof(st->s[0]));
    bcopy(st->y + st->framelen, st->y, (st->buflen - st->framelen)*sizeof(st->y[0]));
    
    return sizeofparm;
}

openlpc_decoder_state *create_openlpc_decoder_state(void)
{
    openlpc_decoder_state *state;
    
    state = (openlpc_decoder_state *)calloc(1, sizeof(openlpc_decoder_state));
    
    return state;
}

void init_openlpc_decoder_state(openlpc_decoder_state *st, int framelen)
{
    int i, j;
    
    st->Oldper = 0.0f;
    st->OldG = 0.0f;
    for (i = 0; i <= LPC_FILTORDER; i++) {
        st->Oldk[i] = 0.0f;
        st->bp[i] = 0.0f;
    }
    st->pitchctr = 0;
    st->exc = 0.0f;
    logmaxminper = (float)log((float)MAXPER/MINPER);
    
    for(i=0, j=0; i<sizeof(parambits)/sizeof(parambits[0]); i++) {
        j += parambits[i];
    }
    sizeofparm = (j+7)/8 + 2;

    /* test for a valid frame len? */
    st->framelen = framelen;
    st->buflen = framelen*3/2;
}

/* LPC Synthesis (decoding) */

int openlpc_decode(sp_data *sp, unsigned char *parm, short *buf, openlpc_decoder_state *st)
{
    int i, j, flen=st->framelen;
    float per, gain, k[LPC_FILTORDER+1];
    float f, u, newgain, Ginc, Newper, perinc;
    float Newk[LPC_FILTORDER+1], kinc[LPC_FILTORDER+1];
    float gainadj;
    int hframe;
    float hper[2];
    int ii;
    float bp0, bp1, bp2, bp3, bp4, bp5, bp6, bp7, bp8, bp9, bp10;
            float kj;
    
    bp0 = st->bp[0];
    bp1 = st->bp[1];
    bp2 = st->bp[2];
    bp3 = st->bp[3];
    bp4 = st->bp[4];
    bp5 = st->bp[5];
    bp6 = st->bp[6];
    bp7 = st->bp[7];
    bp8 = st->bp[8];
    bp9 = st->bp[9];
    bp10 = st->bp[10];
    
    per = (float)(parm[0]);
    
    per = (float)(per == 0? 0: REAL_MINPER * exp(per/(1<<8) * logmaxminper));

    hper[0] = hper[1] = per;

    if((parm[1] & 0x1) == 0) hper[0] = 0;
    if((parm[1] & 0x2) == 0) hper[1] = 0;
    
#ifdef LINEAR_G_Q
    gain = (float)parm[1] / (1<<7);
#else
    gain = (float)parm[1] / 256.f;
    gain = (float)((exp(gain) - 1)/((2.718-1.f)/10));
#endif
    
    k[0] = 0.0;
    
    for (i=LPC_FILTORDER-1; i >= 0; i--) {
        int bitamount = parambits[i];
        int bitc8 = 8-bitamount;
        /* casting to char should set the sign properly */
        char c = (char)(parm[2] << bitc8);
        
        for(j=2; j<sizeofparm; j++)
            parm[j] = (unsigned char)((parm[j] >> bitamount) | (parm[j+1] << bitc8)); 
        
        k[i+1] = ((float)c / (1<<7));
#ifdef ARCSIN_Q
        if(i<2) k[i+1] = (float)sin(M_PI/2*k[i+1]);
#endif
    }
    
    /* k[] are the same in the two subframes */
    for (i=1; i <= LPC_FILTORDER; i++) {
        Newk[i] = st->Oldk[i];
        kinc[i] = (k[i] - st->Oldk[i]) / flen;
    }
    
    /* Loop on two half frames */
    
    for(hframe=0, ii=0; hframe<2; hframe++) {
        
        Newper = st->Oldper;
        newgain = st->OldG;
        
        Ginc = (gain - st->OldG) / (flen/2);
        per = hper[hframe];
        
        if (per == 0.0) {			 /* if unvoiced */
            gainadj = /* 1.5874 * */ (float)sqrt(3.0f/st->buflen);
        } else {
            gainadj = (float)sqrt(per/st->buflen); 
        }
        
        /* Interpolate period ONLY if both old and new subframes are voiced, gain and K always */ 
        
        if (st->Oldper != 0 && per != 0) {
            perinc = (per - st->Oldper) / (flen/2);
        } else {
            perinc = 0.0f; 
            Newper = per;
        }
        
        if (Newper == 0.f) st->pitchctr = 0;
        
        for (i=0; i < flen/2; i++, ii++) {
            if (Newper == 0.f) {
                u = (float)(((sp_rand(sp)*(1/(1.0f+RAND_MAX))) - 0.5f ) * newgain * gainadj); 
            } else {			/* voiced: send a delta every per samples */
                /* triangular excitation */
                if (st->pitchctr == 0) {
                    st->exc = newgain * 0.25f * gainadj;
                    st->pitchctr = (int) Newper;
                } else {
                    st->exc -= newgain/Newper * 0.5f * gainadj;
                    st->pitchctr--;
                }
                u = st->exc;
            }
            f = u;
	        /* excitation */
            kj = Newk[10];
            f -= kj * bp9;
            bp10 = bp9 + kj * f;

            kj = Newk[9];
            f -= kj * bp8;
            bp9 = bp8 + kj * f;

            kj = Newk[8];
            f -= kj * bp7;
            bp8 = bp7 + kj * f;

            kj = Newk[7];
            f -= kj * bp6;
            bp7 = bp6 + kj * f;

            kj = Newk[6];
            f -= kj * bp5;
            bp6 = bp5 + kj * f;

            kj = Newk[5];
            f -= kj * bp4;
            bp5 = bp4 + kj * f;

            kj = Newk[4];
            f -= kj * bp3;
            bp4 = bp3 + kj * f;

            kj = Newk[3];
            f -= kj * bp2;
            bp3 = bp2 + kj * f;

            kj = Newk[2];
            f -= kj * bp1;
            bp2 = bp1 + kj * f;

            kj = Newk[1];
            f -= kj * bp0;
            bp1 = bp0 + kj * f;

            bp0 = f;
            u = f;

            if (u  < -0.9999f) {
                u = -0.9999f;
            } else if (u > 0.9999f) {
                u = 0.9999f;
            }

            buf[ii] = (short)lrintf(u * 32767.0f);

            Newper += perinc;
            newgain += Ginc;
            for (j=1; j <= LPC_FILTORDER; j++) Newk[j] += kinc[j];

        }

        st->Oldper = per;
        st->OldG = gain;
    }
    st->bp[0] = bp0;
    st->bp[1] = bp1;
    st->bp[2] = bp2;
    st->bp[3] = bp3;
    st->bp[4] = bp4;
    st->bp[5] = bp5;
    st->bp[6] = bp6;
    st->bp[7] = bp7;
    st->bp[8] = bp8;
    st->bp[9] = bp9;
    st->bp[10] = bp10;

    for (j=1; j <= LPC_FILTORDER; j++) st->Oldk[j] = k[j];

    return flen;
}

void destroy_openlpc_decoder_state(openlpc_decoder_state *st)
{
    if(st != NULL)
    {
        free(st);
        st = NULL;
    }
}

void openlpc_sr(float sr)
{
    my_fs = sr;
}

size_t openlpc_get_encoder_state_size(void)
{
    return sizeof(openlpc_encoder_state);
}

size_t openlpc_get_decoder_state_size(void)
{
    return sizeof(openlpc_decoder_state);
}
