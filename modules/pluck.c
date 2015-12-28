/*
 * pluck
 * 
 * This code has been extracted from the Csound opcode "pluck"
 * It has been modified to work as a Soundpipe module.
 * 
 * Original Author(s): Barry Vercoe, John ffitch
 * Year: 1991
 * Location: OOps/ugens4.c
 *
 */

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "soundpipe.h"

#define PLUKMIN 64
 
int sp_pluck_create(sp_pluck **p)
{
    *p = malloc(sizeof(sp_pluck));
    return SP_OK;
}

int sp_pluck_destroy(sp_pluck **p)
{
    sp_pluck *pp = *p;
    sp_auxdata_free(&pp->auxch);
    free(*p);
    return SP_OK;
}

int sp_pluck_init(sp_data *sp, sp_pluck *p, SPFLOAT ifreq)
{
    int n;
    int32_t npts, iphs;
    char *auxp;
    SPFLOAT *ap, *fp;
    SPFLOAT phs, phsinc;
    p->amp = 0.5;
    p->ifreq = ifreq;
    p->freq = ifreq;
    if ((npts = (int32_t)(sp->sr / p->ifreq)) < PLUKMIN) {
        npts = PLUKMIN;                  
    }
    
    sp_auxdata_alloc(&p->auxch, (npts + 1) * sizeof(SPFLOAT));
      auxp = p->auxch.ptr;
      p->maxpts = npts;
    ap = (SPFLOAT *)auxp;
    SPFLOAT val = 0;
  for (n=npts; n--; ) {   

    val = (SPFLOAT) ((SPFLOAT) sp_rand(sp) / SP_RANDMAX);
    *ap++ = (val * 2) - 1;
  }
    //*ap = *(SPFLOAT *)auxp;   /* last = copy of 1st */
    p->npts = npts;
    /* tuned pitch convt */
    p->sicps = (npts * 256.0 + 128.0) * (1.0 / sp->sr);
    p->phs256 = 0;
    return SP_OK;
}

int sp_pluck_compute(sp_data *sp, sp_pluck *p, SPFLOAT *trig, SPFLOAT *out)
{
    SPFLOAT *fp;
    int32_t phs256, phsinc, ltwopi, offset;
    SPFLOAT frac, diff;

    phsinc = (int32_t)(p->freq * p->sicps);
    phs256 = p->phs256;
    ltwopi = p->npts << 8;
    //for (n=koffset; n<nsmps; n++) {
      offset = phs256 >> 8;
      fp = (SPFLOAT *)p->auxch.ptr + offset;     /* lookup position   */
      diff = fp[1] - fp[0];
      frac = (SPFLOAT)(phs256 & 255) / 256.0; /*  w. interpolation */
      *out =   (fp[0] + diff*frac) * p->amp; /*  gives output val */
      if ((phs256 += phsinc) >= ltwopi) {
        int nn;
        SPFLOAT newval, preval;
        phs256 -= ltwopi;               
        fp=(SPFLOAT *)p->auxch.ptr;
        preval = fp[0];                
        fp[0] = fp[p->npts];
        fp++;
        nn = p->npts;
          do {          
            /* 1st order recursive filter*/
            preval = (*fp + preval) * 0.5;
            *fp++ = preval;
          } while (--nn);
      }
    //}
    p->phs256 = phs256;
    return SP_OK;
}
