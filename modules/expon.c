/*
 * Expon
 *
 * This code has been extracted from the Csound opcode "expon".
 * It has been modified to work as a Soundpipe module.
 *
 * Original Author(s): Barry Vercoe
 * Year: 1991
 * Location: OOps/ugens1.c
 *
 */

#include <math.h>
#include <stdlib.h>
#include "soundpipe.h"

int sp_expon_create(sp_expon **p)
{
    *p = malloc(sizeof(sp_expon));
    return SP_OK;
}

int sp_expon_destroy(sp_expon **p)
{
    free(*p);
    return SP_OK;
}

static void expon_reinit(sp_data *sp, sp_expon *p)
{
    p->stime = 0;
    p->sdur = p->idur * sp->sr;
    SPFLOAT onedsr = 1.0 / sp->sr;
    if((p->ia * p->ib) > 0.0) {
        p->incr = pow((SPFLOAT)(p->ib / p->ia), onedsr / p->idur);
    } else {
        fprintf(stderr, "Warning: p values must be non-zero\n");
        p->incr = 1;
        p->val = p->ia;
    }

    p->val = p->ia;
}

int sp_expon_init(sp_data *sp, sp_expon *p)
{
    p->ia = 0.000001;
    p->ib = 1;
    p->idur = 1;
    expon_reinit(sp, p);
    p->init = 1;
    return SP_OK;
}

int sp_expon_compute(sp_data *sp, sp_expon *p, SPFLOAT *in, SPFLOAT *out)
{
    if(*in) {
        expon_reinit(sp, p);
        p->init = 0;
    }

    if(p->init) {
        *out = 0;
        return SP_OK;
    }

    if(p->stime < p->sdur) {
        SPFLOAT val = p->val;
        p->val *= p->incr;
        p->stime++;
        *out = val;
    } else {
        *out = p->ib;
    }
    return SP_OK;
}
