#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI		3.14159265358979323846	/* pi */
#endif 

#include "soundpipe.h"

int sp_eqfil_create(sp_eqfil **p)
{
    *p = malloc(sizeof(sp_eqfil));
    return SP_OK;
}

int sp_eqfil_destroy(sp_eqfil **p)
{
    free(*p);
    return SP_OK;
}

int sp_eqfil_init(sp_data *sp, sp_eqfil *p, SPFLOAT freq, SPFLOAT bw, SPFLOAT gain)
{
    p->sr = sp->sr;
    p->z1 = p->z2 = 0.0;
    p->freq = freq;
    p->bw = bw;
    p->gain = gain;

    p->frv = p->freq; p->bwv = p->bw;
    p->d = cos(2 * M_PI * p->frv /p->sr);
    p->c = tan(M_PI * p->bwv / p->sr);
    return SP_OK;
}

int sp_eqfil_compute(sp_data *sp, sp_eqfil *p, SPFLOAT *in, SPFLOAT *out)
{
    SPFLOAT z1 = p->z1, z2 = p->z2, c, d, w, a, y;
    SPFLOAT  g;

    if(p->bw != p->bwv || p->freq != p->frv) {
        SPFLOAT sr = sp->sr;
        p->frv = p->freq; p->bwv = p->bw;
        p->d = cos(2 * M_PI * p->frv / sr);
        p->c = tan(M_PI * p->bwv / sr);
    }

    c = p->c;
    d = p->d;
    a = (1.0 - c) / (1.0 + c);
    g = p->gain;

    w = *in + d * (1.0 + a) * z1 - a * z2;
    y = w * a - d * (1.0 + a) * z1 + z2;
    z2 = z1;
    z1 = w;
    *out = (0.5 * (y + *in + g * (*in - y)));

    p->z1 = z1;
    p->z2 = z2;

return SP_OK;
}
