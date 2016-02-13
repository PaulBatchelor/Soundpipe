/*
 * Foo
 * 
 * This is a dummy module. It doesn't do much.
 * Feel free to use this as a boilerplate template.
 * 
 */

#include <stdlib.h>
#include <math.h>
#include "soundpipe.h"


#define PFRAC1(x)   ((SPFLOAT)((x) & ftp1->lomask) * ftp1->lodiv)

#ifndef M_PI
#define M_PI		3.14159265358979323846
#endif

#define MPIDSR -M_PI/sp->sr

static inline SPFLOAT intpow1(SPFLOAT x, int32_t n)
{
    SPFLOAT ans = 1.0;
    while (n!=0) {
      if (n&1) ans = ans * x;
      n >>= 1;
      x = x*x;
    }
    return ans;
}

static SPFLOAT intpow(SPFLOAT x, int32_t n)
{
    if (n<0) {
      n = -n;
      x = 1.0/x;
    }
    return intpow1(x, n);
}

static int newpulse(sp_data *sp, sp_fog *p, sp_fog_overlap *ovp, SPFLOAT amp,
                    SPFLOAT fund, SPFLOAT ptch)
{
    SPFLOAT octamp = amp, oct;
    SPFLOAT form = ptch / p->ftp1->sicvt, fogcvt = p->fogcvt;
    int32_t rismps, newexp = 0;
    ovp->timrem = (int32_t)(p->dur * sp->sr);

    if ((oct = p->oct) > 0.0) {
      int32_t ioct = (int32_t)oct, bitpat = ~(-1L << ioct);
      if (bitpat & ++p->fofcount)
        return(0);
      if ((bitpat += 1) & p->fofcount)
        octamp *= (1.0) + ioct - oct;
    }
    if (fund == 0.0) ovp->formphs = 0;
    else ovp->formphs = (int32_t)(p->fundphs * form / fund) & SP_FT_PHMASK;

    ovp->forminc = (int32_t)(ptch * fogcvt);

    if (p->band != p->prvband) {
      p->prvband = p->band;
      p->expamp = exp(p->band * MPIDSR);
      newexp = 1;
    }
    if (p->ris >= (1.0 / sp->sr)  && form != 0.0) {
      ovp->risphs = (uint32_t)(ovp->formphs / (fabs(form))
                                    / p->ris);
      ovp->risinc = (int32_t)(p->ftp1->sicvt / p->ris);
      rismps = SP_FT_MAXLEN / ovp->risinc;
    } else {
      ovp->risphs = SP_FT_MAXLEN;
      rismps = 0;
    }

    /* p->spdphs (soundfile ftable index) must be added to
       ovp->formphs (sound ftable reading rate)
       AFTER ovp-risphs is calculated */
    ovp->formphs = (ovp->formphs + p->spdphs) & SP_FT_PHMASK;

    if (newexp || rismps != p->prvsmps) {
      if ((p->prvsmps = rismps))
        p->preamp = intpow(p->expamp, -rismps);
      else p->preamp = 1.0;
    }

    ovp->curamp = octamp * p->preamp;                /* set startamp  */
    ovp->expamp = p->expamp;
    if ((ovp->dectim = (int32_t)(p->dec * sp->sr )) > 0) /*      fnb dec  */
      ovp->decinc = (int32_t)(p->ftp1->sicvt / p->dec);
    ovp->decphs = SP_FT_PHMASK;
    return 1;
}

int sp_fog_create(sp_fog **p)
{
    *p = malloc(sizeof(sp_fog));
    return SP_OK;
}

int sp_fog_destroy(sp_fog **p)
{
    free(*p);
    return SP_OK;
}

int sp_fog_init(sp_data *sp, sp_fog *p, sp_ftbl *wav, sp_ftbl *win, int iolaps, SPFLOAT iphs)
{
    /* legato test, not sure if the last bit (auxch) is correct? */
    //int skip = (*p->iskip != FL(0.0) && p->auxch.auxp != 0);
    //if ((p->ftp1 = csound->FTFind(csound, p->ifna)) != NULL &&
        //(p->ftp2 = csound->FTFind(csound, p->ifnb)) != NULL) {
      sp_fog_overlap *ovp, *nxtovp;
      int32_t olaps;
      p->fogcvt = SP_FT_MAXLEN/(p->ftp1)->size;
      //p->durtogo = (int32)(*p->itotdur * CS_ESR);
      //if (!skip) { /* legato: skip all memory management */
        p->spdphs = 0L;
        if (p->iphs == 0.0) p->fundphs = SP_FT_MAXLEN;
        else p->fundphs = (int32_t)(p->iphs * SP_FT_MAXLEN) & SP_FT_PHMASK;

        olaps = (int32_t)p->iolaps;


        //if (p->iphs > =0.0)
          //csound->AuxAlloc(csound, (size_t)olaps * sizeof(OVERLAP), &p->auxch);
          
        sp_auxdata_alloc(&p->auxch, (size_t)olaps * sizeof(sp_fog_overlap));
        ovp = &p->basovrlap;
        nxtovp = (sp_fog_overlap *) p->auxch.ptr;

        do {
          ovp->nxtact = NULL;
          ovp->nxtfree = nxtovp;              /* link the ovlap spaces */
          ovp = nxtovp++;
        } while (--olaps);

        ovp->nxtact  = NULL;
        ovp->nxtfree = NULL;
        p->fofcount = -1;
        p->prvband = 0.0;
        p->expamp = 1.0;
        p->prvsmps = 0;
        p->preamp = 1.0;
      //}
/* p->speedcod  = (p->XINCODE & 0x8) ? 1 : 0; */ /*out for phs version of fog*/
      p->fmtmod  = 0;
    //}
    return SP_OK;
}

int sp_fog_compute(sp_data *sp, sp_fog *p, SPFLOAT *in, SPFLOAT *out)
{
    return SP_OK;
}
