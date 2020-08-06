/*
 * Butbr
 *
 * This is an implementation of a 2nd-order butterworth
 * band-reject filter, discretized using the bilinear transform.
 *
 * For more information on using the BLT on 2nd-order
 * butterworth filters, see:
 *
 * https://ccrma.stanford.edu/~jos/filters/Example_Second_Order_Butterworth_Lowpass.html
 */

#include <math.h>
#include <stdlib.h>
#include "soundpipe.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int sp_butbr_create(sp_butbr **p)
{
    *p = malloc(sizeof(sp_butbr));
    return SP_OK;
}

int sp_butbr_destroy(sp_butbr **p)
{
    free(*p);
    return SP_OK;
}

int sp_butbr_init(sp_data *sp, sp_butbr *p)
{
    p->freq = 1000;
    p->bw = 1000;
    p->pidsr = M_PI / sp->sr * 1.0;
    p->tpidsr = 2 * M_PI / sp->sr * 1.0;
    p->a[5] = p->a[6] = 0.0;
    p->lfreq = 0.0;
    p->lbw = 0.0;
    return SP_OK;
}

int sp_butbr_compute(sp_data *sp, sp_butbr *p, SPFLOAT *in, SPFLOAT *out)
{
    SPFLOAT *a;
    SPFLOAT t, y;
    SPFLOAT bw, freq;

    if (p->bw <= 0.0) {
      *out = 0;
      return SP_OK;
    }

    a = p->a;
    bw = p->bw;
    freq = p->freq;

    if (bw != p->lbw || freq != p->lfreq) {
        SPFLOAT c, d;
        p->lfreq = freq;
        p->lbw = bw;
        c = tan((SPFLOAT)(p->pidsr * bw));
        d = 2.0 * cos((SPFLOAT)(p->tpidsr * freq));
        a[0] = 1.0 / (1.0 + c);
        a[1] = -d * a[0];
        a[2] = a[0];
        a[3] = a[1];
        a[4] = (1.0 - c) * a[0];
    }

    t = *in - a[3]*a[5] - a[4]*a[6];
    y = t*a[0] + a[1]*a[5] + a[2]*a[6];
    a[6] = a[5];
    a[5] = t;
    *out = y;

    return SP_OK;
}
