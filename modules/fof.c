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
#define kgliss ifmode

static inline SPFLOAT intpow(SPFLOAT x, unsigned n)
{
    SPFLOAT ans = 1.0;

    while (n != 0) {
        if (n & 1)
            ans *= x;
        n >>= 1;
        x *= x;
    }
    return ans;
}

static int newpulse(sp_data *sp,
                    sp_fof *p, sp_fof_overlap *ovp, SPFLOAT *amp, SPFLOAT *fund, SPFLOAT *form)
{
    SPFLOAT   octamp = *amp, oct;
    int32_t   rismps, newexp = 0;

    if ((ovp->timrem = (int32_t)(p->kdur * sp->sr)) > p->durtogo) /* ringtime */
      return(0);
    if ((oct = p->koct) > 0.0) {                   /* octaviation */
      int32_t ioct = (int32_t)oct, bitpat = ~(-1L << ioct);
      if (bitpat & ++p->fofcount)
        return(0);
      if ((bitpat += 1) & p->fofcount)
        octamp *= (1.0 + ioct - oct);
    }
    if (*fund == 0.0)                               /* formant phs */
      ovp->formphs = 0;
    else ovp->formphs = (int32_t)(p->fundphs * *form / *fund) & SP_FT_PHMASK;
    ovp->forminc = (int32_t)(*form * p->ftp1->sicvt);
    if (p->kband != p->prvband) {                    /* bw: exp dec */
      p->prvband = p->kband;
      p->expamp =  exp(p->kband * MPIDSR);
      newexp = 1;
    }
    /* Init grain rise ftable phase. Negative kform values make
       the kris (ifnb) initial index go negative and crash csound.
       So insert another if-test with compensating code. */
    //if (*p->kris >= csound->onedsr && *form != 0.0) {   /* init fnb ris */
    if (p->kris >= (1.0 / sp->sr) && *form != 0.0) {   /* init fnb ris */
      if (*form < 0.0 && ovp->formphs != 0)
        ovp->risphs = (int32_t)((SP_FT_MAXLEN - ovp->formphs) / -*form / p->kris);
      else
        ovp->risphs = (int32_t)(ovp->formphs / *form / p->kris);
      ovp->risinc = (int32_t)(p->ftp1->sicvt / p->kris);
      rismps = SP_FT_MAXLEN / ovp->risinc;
    }
    else {
      ovp->risphs = SP_FT_MAXLEN;
      rismps = 0;
    }
    if (newexp || rismps != p->prvsmps) {            /* if new params */
      if ((p->prvsmps = rismps))                     /*   redo preamp */
        p->preamp = intpow(p->expamp, -rismps);
      else p->preamp = 1.0;
    }
    ovp->curamp = octamp * p->preamp;                /* set startamp  */
    ovp->expamp = p->expamp;
    if ((ovp->dectim = (int32_t)(p->kdec * sp->sr)) > 0) /*  fnb dec  */
      ovp->decinc = (int32_t)(p->ftp1->sicvt / p->kdec);
    ovp->decphs = SP_FT_PHMASK;
    if (!p->foftype) {
      /* Make fof take k-rate phase increment:
         Add current iphs to initial form phase */
      ovp->formphs += (int32_t)(p->iphs * SP_FT_MAXLEN);           /*  krate phs */
      ovp->formphs &= SP_FT_PHMASK;
      /* Set up grain gliss increment: ovp->glissbas will be added to
         ovp->forminc at each pass in fof2. Thus glissbas must be
         equal to kgliss / grain playing time. Also make it harmonic,
         so integer kgliss can represent octaves (ie pow() call). */
      ovp->glissbas = ovp->forminc * (SPFLOAT)pow(2.0, (double)p->kgliss);
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
    //int skip = (*p->iskip != 0.0 && p->auxch.ptr != 0);
    //if ((p->ftp1 = csound->FTFind(csound, p->ifna)) != NULL &&
        //(p->ftp2 = csound->FTFind(csound, p->ifnb)) != NULL) {
      sp_fof_overlap *ovp, *nxtovp;
      int32_t  olaps;
      p->durtogo = (int32_t)(p->itotdur * sp->sr);
      if (1) { /* legato: skip all memory management */
        if (p->iphs == 0.0)                /* if fundphs zero,  */
          p->fundphs = SP_FT_MAXLEN;                  /*   trigger new FOF */
        else p->fundphs = (int32_t)(p->iphs * SP_FT_MAXLEN) & SP_FT_PHMASK;

        olaps = (int32_t)p->iolaps;

        if (p->iphs >= 0.0)
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
        p->fmtmod = (p->ifmode == 0.0) ? 0 : 1;
    //}
    //else return NOTOK;
    p->foftype = 1;
    return SP_OK;
}

int sp_fof_compute(sp_data *sp, sp_fof *p, SPFLOAT *in, SPFLOAT *out)
{
    sp_fof_overlap *ovp;
    sp_ftbl *ftp1, *ftp2;
    SPFLOAT amp, fund, form;
    //uint32_t offset = p->h.insdshead->ksmps_offset;
    //uint32_t early  = p->h.insdshead->ksmps_no_end;
    //uint32_t n, nsmps = CS_KSMPS;
    int32_t fund_inc, form_inc;
    SPFLOAT v1, fract ,*ftab;

    //if (UNLIKELY(p->auxch.auxp==NULL)) goto err1; /* RWD fix */
    amp = p->xamp;
    fund = p->xfund;
    form = p->xform;
    ftp1 = p->ftp1;
    ftp2 = p->ftp2;
    fund_inc = (int32_t)(fund * ftp1->sicvt);
    form_inc = (int32_t)(form * ftp1->sicvt);
    //for (n=offset; n<nsmps; n++) {
      if (p->fundphs & SP_FT_MAXLEN) {               /* if phs has wrapped */
        p->fundphs &= SP_FT_PHMASK;
        //if ((ovp = p->basovrlap.nxtfree) == NULL) goto err2;
        ovp = p->basovrlap.nxtfree;
        if (newpulse(sp, p, ovp, &amp, &fund, &form)) {   /* init new fof */
          ovp->nxtact = p->basovrlap.nxtact;     /* & link into  */
          p->basovrlap.nxtact = ovp;             /*   actlist    */
          p->basovrlap.nxtfree = ovp->nxtfree;
        }
      }
      *out = 0.0;
      ovp = &p->basovrlap;
      while (ovp->nxtact != NULL) {         /* perform cur actlist:  */
        SPFLOAT  result;
        sp_fof_overlap *prvact = ovp;
        ovp = ovp->nxtact;                   /*  formant waveform  */
        fract = PFRAC1(ovp->formphs);        /* from JMC Fog*/
        ftab = ftp1->tbl + (ovp->formphs >> ftp1->lobits);/*JMC Fog*/
        v1 = *ftab++;                           /*JMC Fog*/
        result = v1 + (*ftab - v1) * fract;     /*JMC Fog*/
/*              result = *(ftp1->ftable + (ovp->formphs >> ftp1->lobits) ); */
        if (p->foftype) {
          if (p->fmtmod)
            ovp->formphs += form_inc;           /* inc phs on mode */
          else ovp->formphs += ovp->forminc;
        }
        else {
          /* SPFLOAT ovp->glissbas = kgliss / grain length. ovp->sampct is
             incremented each sample. We add glissbas * sampct to the
             pitch of grain at each a-rate pass (ovp->formphs is the
             index into ifna; ovp->forminc is the stepping factor that
             decides pitch) */
          ovp->formphs += (int32_t)(ovp->forminc + ovp->glissbas * ovp->sampct++);
        }
        ovp->formphs &= SP_FT_PHMASK;
        if (ovp->risphs < SP_FT_MAXLEN) {             /*  formant ris envlp */
          result *= *(ftp2->tbl + (ovp->risphs >> ftp2->lobits) );
          ovp->risphs += ovp->risinc;
        }
        if (ovp->timrem <= ovp->dectim) {       /*  formant dec envlp */
          result *= *(ftp2->tbl + (ovp->decphs >> ftp2->lobits) );
          if ((ovp->decphs -= ovp->decinc) < 0)
            ovp->decphs = 0;
        }
        *out += (result * ovp->curamp);        /*  add wavfrm to out */
        if (--ovp->timrem)                      /*  if fof not expird */
          ovp->curamp *= ovp->expamp;           /*   apply bw exp dec */
        else {
          prvact->nxtact = ovp->nxtact;         /*  else rm frm activ */
          ovp->nxtfree = p->basovrlap.nxtfree;  /*  & ret spc to free */
          p->basovrlap.nxtfree = ovp;
          ovp = prvact;
        }
      }
      p->fundphs += fund_inc;
      if (p->xincod) {
        if (p->ampcod)    amp++;
        if (p->fundcod)   fund_inc = (int32_t)(fund * ftp1->sicvt);
        if (p->formcod)   form_inc = (int32_t)(form * ftp1->sicvt);
      }
      p->durtogo--;
    //}
    return SP_OK;
}
