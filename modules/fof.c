/*
 * Foo
 * 
 * This is a dummy module. It doesn't do much.
 * Feel free to use this as a boilerplate template.
 * 
 */

#include <stdlib.h>
#include "soundpipe.h"

#define PFRAC1(x)   ((SPFLOAT)((x) & ftp1->lomask) * ftp1->lodiv)

static int newpulse(CSOUND *csound,
                    FOFS *p, OVRLAP *ovp, MYFLT *amp, MYFLT *fund, MYFLT *form)
{
    SPFLOAT   octamp = *amp, oct;
    int32_t   rismps, newexp = 0;

    if ((ovp->timrem = (int32_t)(*p->kdur * CS_ESR)) > p->durtogo &&
        (*p->iskip==0.0)) /* ringtime */
      return(0);
    if ((oct = *p->koct) > 0.0) {                   /* octaviation */
      int32_t ioct = (int32_t)oct, bitpat = ~(-1L << ioct);
      if (bitpat & ++p->fofcount)
        return(0);
      if ((bitpat += 1) & p->fofcount)
        octamp *= (1.0 + ioct - oct);
    }
    if (*fund == 0.0)                               /* formant phs */
      ovp->formphs = 0;
    else ovp->formphs = (int32_t)(p->fundphs * *form / *fund) & PHMASK;
    ovp->forminc = (int32_t)(*form * csound->sicvt);
    if (*p->kband != p->prvband) {                    /* bw: exp dec */
      p->prvband = *p->kband;
      p->expamp =  EXP(*p->kband * csound->mpidsr);
      newexp = 1;
    }
    /* Init grain rise ftable phase. Negative kform values make
       the kris (ifnb) initial index go negative and crash csound.
       So insert another if-test with compensating code. */
    if (*p->kris >= csound->onedsr && *form != 0.0) {   /* init fnb ris */
      if (*form < 0.0 && ovp->formphs != 0)
        ovp->risphs = (int32_t)((SP_FT_MAXLEN - ovp->formphs) / -*form / *p->kris);
      else
        ovp->risphs = (int32_t)(ovp->formphs / *form / *p->kris);
      ovp->risinc = (int32_t)(csound->sicvt / *p->kris);
      rismps = SP_FT_MAXLEN / ovp->risinc;
    }
    else {
      ovp->risphs = SP_FT_MAXLEN;
      rismps = 0;
    }
    if (newexp || rismps != p->prvsmps) {            /* if new params */
      if ((p->prvsmps = rismps))                     /*   redo preamp */
        p->preamp = csound->intpow(p->expamp, -rismps);
      else p->preamp = 1.0;
    }
    ovp->curamp = octamp * p->preamp;                /* set startamp  */
    ovp->expamp = p->expamp;
    if ((ovp->dectim = (int32_t)(*p->kdec * CS_ESR)) > 0) /*  fnb dec  */
      ovp->decinc = (int32_t)(csound->sicvt / *p->kdec);
    ovp->decphs = PHMASK;
    if (!p->foftype) {
      /* Make fof take k-rate phase increment:
         Add current iphs to initial form phase */
      ovp->formphs += (int32_t)(*p->iphs * FSP_FT_MAXLEN);           /*  krate phs */
      ovp->formphs &= SP_PHMASK;
      /* Set up grain gliss increment: ovp->glissbas will be added to
         ovp->forminc at each pass in fof2. Thus glissbas must be
         equal to kgliss / grain playing time. Also make it harmonic,
         so integer kgliss can represent octaves (ie pow() call). */
      ovp->glissbas = ovp->forminc * (SPFLOAT)pow(2.0, (double)*p->kgliss);
      /* glissbas should be diff of start & end pitch*/
      ovp->glissbas -= ovp->forminc;
      ovp->glissbas /= ovp->timrem;
      ovp->sampct = 0;   /* Must be reset in case ovp was used before  */
    }
    return 1;
}

int sp_fof_create(sp_fof **p)
{
    *p = malloc(sizeof(sp_fof));
    return SP_OK;
}

int sp_fof_destroy(sp_fof **p)
{
    free(*p);
    return SP_OK;
}

int sp_fof_init(sp_data *sp, sp_fof *p)
{
    int skip = (*p->iskip != 0.0 && p->auxch.ptr != 0);
    //if ((p->ftp1 = csound->FTFind(csound, p->ifna)) != NULL &&
        //(p->ftp2 = csound->FTFind(csound, p->ifnb)) != NULL) {
      sp_fof_overlap *ovp, *nxtovp;
      int32_t  olaps;
      p->durtogo = (int32_t)(*p->itotdur * sp->sr);
      if (1) { /* legato: skip all memory management */
        if (*p->iphs == 0.0)                /* if fundphs zero,  */
          p->fundphs = SP_FT_MAXLEN;                  /*   trigger new FOF */
        else p->fundphs = (int32_t)(*p->iphs * SP_FT_MAXLEN) & SP_FT_PHMASK;

        if (*p->iphs >= 0.0)
          sp_auxdata_alloc(&p->auxch, (size_t)olaps * sizeof(sp_fof_overlap));

        ovp = &p->basovrlap;
        nxtovp = (sp_fof_overlap *) p->auxch.ptr;

        do {
          ovp->nxtact = NULL;
          ovp->nxtfree = nxtovp;                /* link the ovlap spaces */
          ovp = nxtovp++;
        } while (--olaps);
        ovp->nxtact = NULL;
        ovp->nxtfree = NULL;
        p->fofcount = -1;
        p->prvband = 0.0;
        p->expamp = 1.0;
        p->prvsmps = (int32_t)0;
        p->preamp = 1.0;
      } /* end of legato code */
      p->ampcod   = 1;
      p->fundcod  = 1;
      p->formcod  = 1;
      p->xincod   = p->ampcod || p->fundcod || p->formcod;
      if (1)
        p->fmtmod = (*p->ifmode == 0.0) ? 0 : 1;
    //}
    //else return NOTOK;
    p->foftype = 1;
    return SP_OK;
}

int sp_fof_compute(sp_data *sp, sp_fof *p, SPFLOAT *in, SPFLOAT *out)
{
    *out = *in;
    return SP_OK;
}
