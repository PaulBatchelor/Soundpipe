
/* GIVE CREDIT HERE WHERE IT IS DUE PAUL, LOVE PAUL */

#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#define ROOT2 (1.4142135623730950488)

#ifndef M_PI
#define M_PI		3.14159265358979323846	/* pi */
#endif 

#include "soundpipe.h"

int sp_port_create(sp_port **p){
    *p = malloc(sizeof(sp_port));
    return SP_OK;
}

int sp_port_destroy(sp_port **p){
    free(*p);
    return SP_OK;
}

int sp_port_init(sp_data *sp, sp_port *p){
    if(p->isig >= 0){
        p->yt1 = p->isig;
    }
    p->prvhtim = -100.0;
    p->khtim = 0.01;

    p->sr = sp->sr;
    p->onedsr = 1.0/p->sr;
    return SP_OK;
}

int sp_port_compute(sp_data *sp, sp_port *p, SPFLOAT *in, SPFLOAT *out){
    if(p->prvhtim != p->khtim){
        p->c2 = pow(0.5, p->onedsr / p->khtim);
        p->c1 = 1.0 - p->c2;
        p->prvhtim = p->khtim;
    }

    *out = p->yt1 = p->c1 * *in + p->c2 * p->yt1;
    return SP_OK;
}
