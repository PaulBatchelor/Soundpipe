/*
 * Sndwarp
 *
 * This code has been extracted from the Csound opcode "sndwarp".
 * It has been modified to work as a Soundpipe module.
 *
 * Original Author(s): Richard Karpen, John ffitch
 * Year: 1997
 * Location: Opcodes/sndwarp.c
 */

#include <stdlib.h>
#include "soundpipe.h"

#define unirand(x) ((SPFLOAT) sp_rand(x) / SP_RANDMAX)

struct sp_sndwarp_warpsection {
    int32_t    cnt, wsize, flag; /* , section; */
    SPFLOAT ampincr, ampphs, offset;
};


int sp_sndwarp_create(sp_sndwarp **p)
{
    *p = malloc(sizeof(sp_sndwarp));
    return SP_OK;
}

int sp_sndwarp_destroy(sp_sndwarp **p)
{
    sp_sndwarp *pp = *p;
    sp_auxdata_free(&pp->auxch);
    free(*p);
    return SP_OK;
}

int sp_sndwarp_init(sp_data *sp,
                    sp_sndwarp *p,
                    sp_ftbl *ftpSamp,
                    SPFLOAT ibegin,
                    int32_t iwsize,
                    SPFLOAT irandw,
                    int32_t ioverlap,
                    sp_ftbl *ftpWind,
                    int itimemode)
{
    int32_t         i;
    int32_t         nsections;
    sp_sndwarp_warpsection *exp;
    char *auxp;

    p->ibegin = ibegin;
    p->iwsize = iwsize;
    p->irandw = irandw;
    p->ioverlap = ioverlap;
    p->itimemode = itimemode;

    nsections = ioverlap;
    sp_auxdata_alloc(&p->auxch, (size_t)nsections*sizeof(sp_sndwarp_warpsection));
    auxp = p->auxch.ptr;
    p->nsections = nsections;
    p->exp = (sp_sndwarp_warpsection *)auxp;

    p->ftpSamp  = ftpSamp;
    p->sampflen = ftpSamp->size;

    p->ftpWind = ftpWind;
    p->flen    = ftpWind->size;

    p->maxFr   = -1 + ftpSamp->size;
    p->prFlg   = 1;    /* true */
    p->begin   = (int32_t)(ibegin * sp->sr);

    exp        = p->exp;
    iwsize = p->iwsize;
    for (i=0; i< p->ioverlap; i++) {
      if (i==0) {
        exp[i].wsize = (int32_t)iwsize;
        exp[i].cnt = 0;
        exp[i].ampphs = 0.0;
      }
      else {
        exp[i].wsize = (int32_t) (iwsize + (unirand(sp) * (p->irandw)));
        exp[i].cnt=(int32_t)(exp[i].wsize*((SPFLOAT)i/(p->ioverlap)));
        exp[i].ampphs = p->flen*((SPFLOAT)i/(p->ioverlap));
      }
      exp[i].offset = (SPFLOAT)p->begin;
      exp[i].ampincr = (SPFLOAT)p->flen/(exp[i].wsize-1);

    }
    p->ampcode = 1;
    p->timewarpcode = 1;
    p->resamplecode = 1;
    p->amp = 1;
    p->timewarp = 2;
    p->resample = 2;
    return SP_OK;
}

int sp_sndwarp_compute(sp_data *sp, sp_sndwarp *p, SPFLOAT *in, SPFLOAT *out)
{
    /* uint32_t n, nsmps = CS_KSMPS; */
    SPFLOAT       frm_0,frm_1;
    int32_t       base, longphase;
    SPFLOAT       frac, frIndx;
    SPFLOAT       r1, amp, timewarpby, resample;
    /* SPFLOAT r2; */
    sp_sndwarp_warpsection *exp;
    sp_ftbl *ftpWind, *ftpSamp;
    int32_t         i;
    SPFLOAT       v1, v2, windowamp, fract;
    SPFLOAT       flen = (SPFLOAT)p->flen;
    SPFLOAT       iwsize = p->iwsize;
    int32_t         overlap = p->ioverlap;

    r1 = 0;
    /* r2 = 0; */
/*     if (p->OUTOCOUNT >1) memset(r2, 0, nsmps*sizeof(MYFLT)); */
/* /\*     for (i=0; i<nsmps; i++) { *\/ */
/* /\*       *r1++ = FL(0.0); *\/ */
/* /\*       if (p->OUTOCOUNT >1) *r2++ = FL(0.0); *\/ */
/* /\*     } *\/ */
    exp = p->exp;
    ftpWind = p->ftpWind;
    ftpSamp = p->ftpSamp;

    for (i=0; i<overlap; i++) {
      resample = p->resample;
      timewarpby = p->timewarp;
      amp = p->amp;
     /* for (n=offset; n<nsmps;n++) { */
        if (exp[i].cnt < exp[i].wsize) goto skipover;

        if (p->itimemode!=0)
          exp[i].offset=(sp->sr * timewarpby)+p->begin;
        else
          exp[i].offset += (SPFLOAT)exp[i].wsize/(timewarpby);

        exp[i].cnt=0;
        exp[i].wsize = (int32_t) (iwsize + (unirand(sp) * (p->irandw)));
        exp[i].ampphs = 0.0;
        exp[i].ampincr = flen/(exp[i].wsize-1);

      skipover:

        frIndx =(SPFLOAT)((exp[i].cnt * resample)  + exp[i].offset);
        exp[i].cnt += 1;
        if (frIndx > (SPFLOAT)p->maxFr) { /* not past last one */
          frIndx = (SPFLOAT)p->maxFr;
          if (p->prFlg) {
            p->prFlg = 0;   /* false */
            fprintf(stderr, "SNDWARP at last sample frame");
          }
        }
        longphase = (int32_t)exp[i].ampphs;
        if (longphase > p->flen-1) longphase = p->flen-1;
        v1 = *(ftpWind->tbl + longphase);
        v2 = *(ftpWind->tbl + longphase + 1);
        fract = (SPFLOAT)(exp[i].ampphs - (int32_t)exp[i].ampphs);
        windowamp = v1 + (v2 - v1)*fract;
        exp[i].ampphs += exp[i].ampincr;

        base = (int32_t)frIndx;    /* index of basis frame of interpolation */
        frac = ((SPFLOAT)(frIndx - (SPFLOAT)base));
        frm_0 = *(ftpSamp->tbl + base);
        frm_1 = *(ftpSamp->tbl + (base+1));
        if (frac != 0.0) {
          r1 += ((frm_0 + frac*(frm_1-frm_0)) * windowamp) * amp;
          /* if (i==0) */
          /*  if (p->OUTOCOUNT > 1) */
          /*    r2 += (frm_0 + frac*(frm_1-frm_0)) * amp; */
        }
        else {
          r1 += (frm_0 * windowamp) * amp;
          /* if (i==0) */
          /*   if (p->OUTOCOUNT > 1) */
          /*     r2 += frm_0 * amp; */
        }
        if (p->ampcode) amp++;
        if (p->timewarpcode) timewarpby++;
        if (p->resamplecode) resample++;
      /* } */
    }

    *out = r1;
    return SP_OK;
}
