#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI		3.14159265358979323846	/* pi */
#endif 

#include "soundpipe.h"

int sp_reson_create(sp_reson **p)
{
    *p = malloc(sizeof(sp_reson));
    return SP_OK;
}

int sp_reson_destroy(sp_reson **p)
{
    free(*p);
    return SP_OK;
}

int sp_reson_init(sp_data *sp, sp_reson *p, SPFLOAT cutoff, SPFLOAT bw)
{
    //need to add cutoff and bw??
    p->scale = 0;
    p->cutoff = cutoff;
    p->bw = bw;
    p->prvcutoff = p->prvbw = -100.0;
    p->tpidsr = (2.0 * M_PI) / sp->sr * 1.0;
    p->yt1 = p->yt2 = 0.0;
    return SP_OK;
}


int sp_reson_compute(sp_data *sp, sp_reson *p, SPFLOAT *in, SPFLOAT *out)
{
    SPFLOAT c3p1, c3t4, omc3, c2sqr;
    SPFLOAT yt1, yt2, c1 = p->c1, c2 = p->c2, c3 = p->c3;
    int flag;

    yt1 = p->yt1; yt2 = p->yt2;
    
    SPFLOAT yt0;
    SPFLOAT cf = p->cutoff;
    SPFLOAT bw = fabs(p->bw);
    if (cf != p->prvcutoff) {
    p->prvcutoff = cf;
    p->cosf = cos(cf * (p->tpidsr));
    flag = 1;                 /* Mark as changed */
    }
    if (bw != p->prvbw) {
    p->prvbw = bw;
    c3 = p->c3 = exp(bw * (-1.0 * p->tpidsr));
    flag = 1;                /* Mark as changed */
    }
    if (flag) {
        c3p1 = c3 + 1.0;
        c3t4 = c3 * 4.0;
        omc3 = 1.0 - c3;
        c2 = p->c2 = c3t4 * p->cosf / c3p1;               /* -B, so + below */
        c2sqr = c2 * c2;
        c1 = p->c1 = 1.0;
        flag = 0;
    }
    yt0 = c1 * *in  + c2 * yt1 - c3 * yt2;
    *out = yt0;
    yt2 = yt1;
    yt1 = yt0;
    p->yt1 = yt1; p->yt2 = yt2; /* Write back for next cycle */
    return SP_OK;
    }
