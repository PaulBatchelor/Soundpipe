/*
 * PTrack
 *
 * This code has been extracted from the Csound opcode "ptrack".
 * It has been modified to work as a Soundpipe module.
 *
 * Original Author(s): Victor Lazzarini, Miller Puckette (Original Algorithm)
 * Year: 2007
 * Location: Opcodes/pitchtrack.c
 *
 */


#include <stdlib.h>
#include <math.h>
#include "soundpipe.h"

#define MINFREQINBINS 5
#define MAXHIST 3
#define MAXWINSIZ 8192
#define MINWINSIZ 128
#define DEFAULTWINSIZ 1024
#define NPREV 20
#define MAXPEAKNOS 100
#define DEFAULTPEAKNOS 20
#define MINBW 0.03
#define BINPEROCT 48
#define BPEROOVERLOG2 69.24936196
#define FACTORTOBINS 4/0.0145453
#define BINGUARD 10
#define PARTIALDEVIANCE 0.023
#define DBSCAL 3.333
#define DBOFFSET -92.3
#define MINBIN 3
#define MINAMPS 40
#define MAXAMPS 50


#define THRSH 10.

#define COEF1 ((SPFLOAT)(.5 * 1.227054))
#define COEF2 ((SPFLOAT)(.5 * -0.302385))
#define COEF3 ((SPFLOAT)(.5 * 0.095326))
#define COEF4 ((SPFLOAT)(.5 * -0.022748))
#define COEF5 ((SPFLOAT)(.5 * 0.002533))
#define FLTLEN 5

#define NPARTIALONSET ((int)(sizeof(partialonset)/sizeof(SPFLOAT)))

#ifndef M_PI
#define M_PI		3.14159265358979323846
#endif


/*TODO: rename these structs */

typedef struct histopeak
{
  SPFLOAT hpitch;
  SPFLOAT hvalue;
  SPFLOAT hloud;
  int hindex;
  int hused;
} HISTOPEAK;

typedef struct peak
{
  SPFLOAT pfreq;
  SPFLOAT pwidth;
  SPFLOAT ppow;
  SPFLOAT ploudness;
} PEAK;

int sp_ptrack_create(sp_ptrack **p)
{
    *p = malloc(sizeof(sp_ptrack));
    return SP_OK;
}

int sp_ptrack_destroy(sp_ptrack **p)
{
    free(*p);
    return SP_OK;
}

int sp_ptrack_init(sp_data *sp, sp_ptrack *p, int ihopsize, int ipeaks)
{
    p->size = ihopsize;

    int i, winsize = p->size*2, powtwo, tmp;
    SPFLOAT *tmpb;

    /*TODO: fix this warning */
    if (winsize < MINWINSIZ || winsize > MAXWINSIZ) {
      //csound->Warning(csound, Str("ptrack: FFT size out of range; using %d\n"),
      //                winsize = DEFAULTWINSIZ);
      fprintf(stderr, "woops\n");
      return SP_NOT_OK;
    }

    tmp = winsize;
    powtwo = -1;

    while (tmp) {
      tmp >>= 1;
      powtwo++;
    }

    if (winsize != (1 << powtwo)) {
      //csound->Warning(csound, Str("ptrack: FFT size not a power of 2; using %d\n"),
       //               winsize = (1 << powtwo));
      fprintf(stderr, "woops\n");
      return SP_NOT_OK;
    }
    p->hopsize = p->size;
    sp_auxdata_alloc(&p->signal, p->hopsize * sizeof(SPFLOAT));

    //csound->AuxAlloc(csound, (p->hopsize*2 + 4*FLTLEN)*sizeof(MYFLT), &p->prev);
    sp_auxdata_alloc(&p->prev, (p->hopsize*2 + 4*FLTLEN)*sizeof(SPFLOAT));

    //if (!p->sin.auxp || p->sin.size < (p->hopsize*2)*sizeof(MYFLT)) {
    //  csound->AuxAlloc(csound, (p->hopsize*2)*sizeof(MYFLT), &p->sin);
    //}
    sp_auxdata_alloc(&p->sin, (p->hopsize*2)*sizeof(SPFLOAT));

    //if (!p->spec2.auxp || p->spec2.size < (winsize*4 + 4*FLTLEN)*sizeof(MYFLT)) {
    //  csound->AuxAlloc(csound, (winsize*4 + 4*FLTLEN)*sizeof(MYFLT), &p->spec2);
    //}
    sp_auxdata_alloc(&p->spec2, (winsize*4 + 4*FLTLEN)*sizeof(SPFLOAT));

    //if (!p->spec1.auxp || p->spec1.size < (winsize*4)*sizeof(MYFLT)) {
    //  csound->AuxAlloc(csound, (winsize*4)*sizeof(MYFLT), &p->spec1);
    //}
    sp_auxdata_alloc(&p->spec1, (winsize*4)*sizeof(SPFLOAT));

    for (i = 0, tmpb = (SPFLOAT *)p->signal.ptr; i < p->hopsize; i++)
      tmpb[i] = 0.0;
    for (i = 0, tmpb = (SPFLOAT *)p->prev.ptr; i < winsize + 4 * FLTLEN; i++)
      tmpb[i] = 0.0;
    for (i = 0, tmpb = (SPFLOAT *)p->sin.ptr; i < p->hopsize; i++)
      tmpb[2*i] =   (SPFLOAT) cos((M_PI*i)/(winsize)),
        tmpb[2*i+1] = -(SPFLOAT)sin((M_PI*i)/(winsize));

    p->cnt = 0;
    if (p->peak == 0 || p->peak > MAXPEAKNOS)
      p->numpks = DEFAULTPEAKNOS;
    else
      p->numpks = p->peak;

    //if (!p->peakarray.auxp || p->peakarray.size < (p->numpks+1)*sizeof(PEAK)) {
    //  csound->AuxAlloc(csound, (p->numpks+1)*sizeof(PEAK), &p->peakarray);
    //}

    sp_auxdata_alloc(&p->peakarray, (p->numpks+1)*sizeof(PEAK));

    p->cnt = 0;
    p->histcnt = 0;
    p->sr = sp->sr;
    for (i = 0; i < NPREV; i++) p->dbs[i] = -144.0;
    p->amplo = MINAMPS;
    p->amphi = MAXAMPS;
    p->npartial = 7;
    //p->dbfs = FL(32768.0)/csound->e0dbfs;
    p->dbfs = 1.0;
    p->prevf = p->cps = 100.0;

    return SP_OK;
}

int sp_ptrack_compute(sp_data *sp, sp_ptrack *p, SPFLOAT *in, SPFLOAT *out)
{
    *out = *in;
    return SP_OK;
}
