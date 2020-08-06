/*
 * Butbp
 *
 * This is an implementation of a 2nd-order butterworth
 * bandpass filter, discretized using the bilinear transform.
 *
 * For more information on using the BLT on 2nd-order
 * butterworth filters, see:
 *
 * https://ccrma.stanford.edu/~jos/filters/Example_Second_Order_Butterworth_Lowpass.html
 */

#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#define ROOT2 (1.4142135623730950488)

#ifndef M_PI
#define M_PI		3.14159265358979323846	/* pi */
#endif

#include "soundpipe.h"

int sp_butbp_create(sp_butbp **p)
{
    *p = malloc(sizeof(sp_butbp));
    return SP_OK;
}

int sp_butbp_destroy(sp_butbp **p)
{
    free(*p);
    return SP_OK;
}

int sp_butbp_init(sp_data *sp, sp_butbp *p)
{
    p->freq = 1000;
    p->bw = 10;
    p->pidsr = M_PI / sp->sr * 1.0;
    p->tpidsr = 2 * M_PI / sp->sr * 1.0;
    p->a[5] = p->a[6] = 0.0;
    p->lfreq = 0.0;
    p->lbw = 0.0;
    return SP_OK;
}

int sp_butbp_compute(sp_data *sp, sp_butbp *p, SPFLOAT *in, SPFLOAT *out)
{
    SPFLOAT *a;
    SPFLOAT t, y;
    SPFLOAT bw, fr;

    a = p->a;
    if (p->bw <= 0.0) {
       *out = 0;
       return SP_OK;
    }

    bw = p->bw;
    fr = p->freq;

    if (bw != p->lbw || fr != p->lfreq) {
        SPFLOAT c, d;
        p->lfreq = fr;
        p->lbw = bw;

        /* Perform BLT and store components */
        c = 1.0 / tan((SPFLOAT)(p->pidsr * bw));
        d = 2.0 * cos((SPFLOAT)(p->tpidsr * fr));
        a[0] = 1.0 / (1.0 + c);
        a[1] = 0.0;
        a[2] = -a[0];
        a[3] = - c * d * a[0];
        a[4] = (c - 1.0) * a[0];
    }

    /* a5 = t(n - 1); a6 = t(n - 2) */
    t = *in - a[3]*a[5] - a[4]*a[6];
    y = t*a[0] + a[1]*a[5] + a[2]*a[6];
    a[6] = a[5];
    a[5] = t;
    *out = y;

    return SP_OK;
}
