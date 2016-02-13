/*
 * Foo
 * 
 * This is a dummy module. It doesn't do much.
 * Feel free to use this as a boilerplate template.
 * 
 */

#include <stdlib.h>
#include "soundpipe.h"

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
