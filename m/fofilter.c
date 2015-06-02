#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "soundpipe.h"


int sp_fofilter_create(sp_fofilter **p){
    *p = malloc(sizeof(sp_fofilter));
    return SP_OK;
}
int sp_fofilter_destroy(sp_fofilter **p){
    free(*p);
    return SP_OK;
}

int sp_fofilter_init(sp_data *sp, sp_fofilter *p){
   p->tpidsr = 2.0*M_PI / sp->sr;
   p->sr = sp->sr;

   p->freq = 1000;
   p->ris = 0.007;
   p->dec = 0.04;
   p->istor = 0.0;

   int i;
   if (p->istor==0.0){
        for (i=0; i<4; i++)
         p->delay[i] = 0.0;
   }
   return SP_OK;
}

int sp_fofilter_compute(sp_data *sp, sp_fofilter *p, SPFLOAT *in, SPFLOAT *out){

    SPFLOAT  freq = p->freq;
    SPFLOAT  ris = p->ris;
    SPFLOAT  dec = p->dec;
    SPFLOAT  *delay = p->delay,ang=0,fsc,rrad1=0,rrad2=0;
    SPFLOAT  w1,y1,w2,y2;
    SPFLOAT lfrq = -1.0, lrs = -1.0, ldc = -1.0;
      
      SPFLOAT frq = freq;
      SPFLOAT rs = ris; 
      SPFLOAT dc = dec;
      if (frq != lfrq || rs != lrs || dc != ldc) {
        lfrq = frq; lrs = rs; ldc = dc;
        ang = (SPFLOAT)p->tpidsr*frq;         /* pole angle */
        fsc = sin(ang) - 3.0;                      /* freq scl   */

        rrad1 =  pow(10.0, fsc/(dc*sp->sr));  /* filter radii */
        rrad2 =  pow(10.0, fsc/(rs*sp->sr));
      }

      w1  = *in + 2.0*rrad1*cos(ang)*delay[0] - rrad1*rrad1*delay[1];
      y1 =  w1 - delay[1];
      delay[1] = delay[0];
      delay[0] = w1;

      w2  = *in + 2.0*rrad2*cos(ang)*delay[2] - rrad2*rrad2*delay[3];
      y2 =  w2 - delay[3];
      delay[3] = delay[2];
      delay[2] = w2;

      *out = (SPFLOAT) (y1 - y2);

    return SP_OK;
}
