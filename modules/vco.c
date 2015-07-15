/*
 * VCO
 * 
 * This code has been extracted from the Csound opcode "vco".
 * It has been modified to work as a Soundpipe module.
 * 
 * Original Author(s): Hans Mikelson
 * Year: 1998
 * Location: Opcodes/biquad.c
 *
 */

#include <stdlib.h>
#include "soundpipe.h"

int sp_vco_create(sp_vco **p)
{
    *p = malloc(sizeof(sp_vco));
    return SP_OK;
}

int sp_vco_destroy(sp_vco **p)
{
    free(*p);
    return SP_OK;
}

int sp_vco_init(sp_data *sp, sp_vco *p, SPFLOAT freq)
{
    p->maxd = 1;
    p->iphs = 0;
    p->leak = 1; 
    p->inyq = 0.5;
    
    uint32 ndel = (uint32)(p->maxd * CS_ESR);

    sp_ftbl_create(sp, &p->ftp, 4096); 
    sp_gen_sine(&p->ftp);

    if (p->iphs >= 0.0)
      p->lphs = (int32_t)(p->iphs * 0.5 * SP_FT_MAXLEN);
    else {
      printf("Initial value of lphs set to zero\n");
      p->lphs = 0;
    }

    //p->ampcod = IS_ASIG_ARG(p->xamp) ? 1 : 0;
    //p->cpscod = IS_ASIG_ARG(p->xcps) ? 1 : 0;

    if (p->iskip == 0.0) {
      p->ynm1 = (p->wave == 1.0) ? -0.5 : 0.0;
      p->ynm2 = 0.0;
    }

    /* finished setting up buzz now set up internal vdelay */

    if (ndel == 0) ndel = 1;    /* fix due to Troxler */

    sp_auxdata_alloc(sp, p->aux, ndel * sizeof(SPFLOAT));

    p->left = 0;

    if (p->leak <= 0.0 || p->leak >= 1.0) {
      p->leaky = (p->wave == 3.0) ? 0.995 : 0.999;
    } else {
      p->leaky = *p->leak;
    }
    p->nyq = p->inyq;

    return SP_OK;
}

int sp_vco_compute(sp_data *sp, sp_vco *p, SPFLOAT *in, SPFLOAT *out)
{
    FUNC  *ftp;
    MYFLT *ar, *ampp, *cpsp, *ftbl;
    int32  phs, inc, lobits, dwnphs, tnp1, lenmask, maxd, indx;
    MYFLT leaky, /*rtfqc,*/ amp, fqc;
    MYFLT sicvt2, over2n, scal, num, denom, pulse = FL(0.0), saw = FL(0.0);
    MYFLT sqr = FL(0.0), tri = FL(0.0);
    uint32_t offset = p->h.insdshead->ksmps_offset;
    uint32_t early  = p->h.insdshead->ksmps_no_end;
    uint32_t n, nsmps = CS_KSMPS;
    int   knh;

    /* VDelay Inserted here */
    MYFLT *buf = (MYFLT *)p->aux.auxp;
    MYFLT fv1, out1;
    int32  v1, v2;
    int wave = (int)MYFLT2LONG(*p->wave); /* Save recalculation and also round */

    leaky = p->leaky;

    ftp = p->ftp;
    if (UNLIKELY(buf==NULL || ftp==NULL)) goto err1;            /* RWD fix */
    maxd = (uint32) (*p->maxd * CS_ESR);
    if (UNLIKELY(maxd == 0)) maxd = 1;    /* Degenerate case */
    indx = p->left;
    /* End of VDelay insert */

    ftbl = ftp->ftable;
    sicvt2 = csound->sicvt * FL(0.5);  /* for theta/2 */
    lobits = ftp->lobits;
    lenmask = ftp->lenmask;
    ampp = p->xamp;
    cpsp = p->xcps;
    fqc = *cpsp;
    //rtfqc = SQRT(fqc);
    knh = (int)(CS_ESR*p->nyq/fqc);
    if (UNLIKELY((n = (int)knh) <= 0)) {
      csound->Warning(csound, "knh=%x nyq=%f fqc=%f\n"
                      "vco knh (%d) <= 0; taken as 1\n", knh, p->nyq, fqc, n);
      n = 1;
    }
    tnp1 = n + n + 1;           /* calc 2n + 1 */
    over2n = FL(0.5) / n;

    amp  = *ampp;
    scal = over2n;
    inc = (int32)(fqc * sicvt2);
    ar = p->ar;
    phs = p->lphs;
    if (UNLIKELY(offset)) memset(ar, '\0', offset*sizeof(MYFLT));
    if (UNLIKELY(early)) {
      nsmps -= early;
      memset(&ar[nsmps], '\0', early*sizeof(MYFLT));
    }

/*-----------------------------------------------------*/
/* PWM Wave                                            */
/*-----------------------------------------------------*/
    if (wave==2) {
      MYFLT pw = *p->pw;
      for (n=offset; n<nsmps; n++) {
        dwnphs = phs >> lobits;
        denom = *(ftbl + dwnphs);
        if (denom > FL(0.00001) || denom < -FL(0.00001)) {
          num = *(ftbl + (dwnphs * tnp1 & lenmask));
          pulse = (num / denom - FL(1.0)) * scal;
        }
        else pulse = FL(1.0);
        phs += inc;
        phs &= PHMASK;
        if (p->ampcod) {
          amp  = ampp[n];
          scal = over2n;        /* Why is this needed?? */
        }
        if (p->cpscod) {
          fqc = cpsp[n];
          inc  = (int32)(fqc* sicvt2);
        }

        /* VDelay inserted here */
        buf[indx] = pulse;
        fv1 = (MYFLT) indx - CS_ESR * pw / fqc;

        v1 = (int32) fv1;
        if (fv1 < FL(0.0)) v1--;
        fv1 -= (MYFLT) v1;
        /* Make sure Inside the buffer */
        while (v1 >= maxd)
          v1 -= maxd;
        while (v1 < 0L)
          v1 += maxd;
        /* Find next sample for interpolation      */
        v2 = (v1 < (maxd - 1L) ? v1 + 1L : 0L);
        out1 = buf[v1] + fv1 * (buf[v2] - buf[v1]);

        if (++indx == maxd) indx = 0;             /* Advance current pointer */
        /* End of VDelay */

        sqr  = pulse - out1 + leaky*p->ynm1;
        p->ynm1 = sqr;
        ar[n]  = (sqr + pw - FL(0.5)) * FL(1.9) * amp;
      }
    }

    /*-----------------------------------------------------*/
    /* Triangle Wave                                       */
    /*-----------------------------------------------------*/
    else if (wave==3) {
      MYFLT pw = *p->pw;
      for (n=offset; n<nsmps; n++) {
        dwnphs = phs >> lobits;
        denom = *(ftbl + dwnphs);
        if (denom > FL(0.0002) || denom < -FL(0.0002)) {
          num = *(ftbl + (dwnphs * tnp1 & lenmask));
          pulse = (num / denom - FL(1.0)) * scal;
        }
        /* else pulse = *ampp; */
        else pulse = FL(1.0);
        phs += inc;
        phs &= PHMASK;
        if (p->ampcod) {
          /*          scal = over2n;       */ /* Why is this needed?? */
          amp = ampp[n];
        }
        if (p->cpscod) {
          fqc = cpsp[n];
          inc  = (int32)(fqc* sicvt2);
        }

        /* VDelay inserted here */
        buf[indx] = pulse;
        fv1 = (MYFLT) indx - CS_ESR * pw / fqc;

        v1 = (int32) fv1;
        if (fv1 < FL(0.0)) v1--;
        fv1 -= (MYFLT) v1;
        /* Make sure Inside the buffer */
        while (v1 >= maxd)
          v1 -= maxd;
        while (v1 < 0L)
          v1 += maxd;
        /* Find next sample for interpolation      */
        v2 = (v1 < (maxd - 1L) ? v1 + 1L : 0L);
        out1 = buf[v1] + fv1 * (buf[v2] - buf[v1]);

        if (UNLIKELY(++indx == maxd)) indx = 0;  /* Advance current pointer */
        /* End of VDelay */

        /* Integrate twice and ouput */
        sqr  = pulse - out1 + leaky*p->ynm1;
        tri  = sqr + leaky*p->ynm2;
        p->ynm1 = sqr;
        p->ynm2 = tri;
        ar[n] =  tri * amp * fqc
                 / (CS_ESR * FL(0.42) * (FL(0.05) + pw - pw * pw));
      }
    }
    /*-----------------------------------------------------*/
    /* Sawtooth Wave                                       */
    /*-----------------------------------------------------*/
    else {
      for (n=offset; n<nsmps; n++) {
        dwnphs = phs >> lobits;
        denom = *(ftbl + dwnphs);
        if (denom > FL(0.0002) || denom < -FL(0.0002)) {
          num = *(ftbl + (dwnphs * tnp1 & lenmask));
          pulse = (num / denom - FL(1.0)) * scal;
        }
        /* else pulse = *ampp; */
        else pulse = FL(1.0);
        phs += inc;
        phs &= PHMASK;
        if (p->ampcod) {
          /* scal = *(++ampp) * over2n; */
          /*          scal = over2n;        *//* Why is this needed?? */
          amp = ampp[n];
        }
        if (p->cpscod) {
          fqc = cpsp[n];
          inc  = (int32)(fqc*sicvt2);
        }

        saw  = pulse + leaky*p->ynm1;
        p->ynm1 = saw;
        ar[n] = saw*FL(1.5)*amp;
      }
    }

    p->left = indx;
    p->lphs = phs;
    return SP_OK;
}
