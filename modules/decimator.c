#include <stdlib.h>
#include <math.h>
#include "soundpipe.h"

int sp_decimator_create(sp_decimator **p)
{
    *p = malloc(sizeof(sp_decimator));
    return SP_OK;
}

int sp_decimator_destroy(sp_decimator **p)
{
    sp_decimator *pp = *p;
    sp_fold_destroy(&pp->fold);
    free(*p);
    return SP_OK;
}

int sp_decimator_init(sp_data *sp, sp_decimator *p)
{
    p->bit = 8;
    p->srate = 10000;
    sp_fold_create(&p->fold);
    sp_fold_init(sp, p->fold);
    return SP_OK;
}

int sp_decimator_compute(sp_data *sp, sp_decimator *p, SPFLOAT *in, SPFLOAT *out)
{
    SPFLOAT bits = pow(2, p->bit);
    SPFLOAT foldamt = sp->sr / p->srate;
    SPFLOAT sig;
    *out = *in;
    *out += 32768;
    *out *= (bits / 65536.0);
    *out = *out;
    *out = *out * (65536.0 / bits) - 32768;
    sig = *out;
    p->fold->incr = foldamt;
    sp_fold_compute(sp, p->fold, &sig, out);
    return SP_OK;
}
