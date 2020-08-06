/*
 * Buthp
 *
 * This is an implementation of a 2nd-order butterworth
 * highpass filter, discretized using the bilinear transform.
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
#define M_PI 3.14159265358979323846
#endif

#include "soundpipe.h"

static int filter(SPFLOAT *in, SPFLOAT *out, SPFLOAT *a)
{
    SPFLOAT t, y;

    /* a5 = t(n - 1); a6 = t(n - 2) */
    t = *in - a[3]*a[5] - a[4]*a[6];
    y = t*a[0] + a[1]*a[5] + a[2]*a[6];
    a[6] = a[5];
    a[5] = t;
    *out = y;
    return SP_OK;
}


int sp_buthp_create(sp_buthp **p)
{
    *p = malloc(sizeof(sp_buthp));
    return SP_OK;
}

int sp_buthp_destroy(sp_buthp **p)
{
    free(*p);
    return SP_OK;
}

int sp_buthp_init(sp_data *sp, sp_buthp *p)
{
    p->freq = 1000;
    p->pidsr = M_PI / sp->sr * 1.0;
    p->a[5] = p->a[6] = 0.0;
    p->lfreq = 0.0;
    return SP_OK;
}

int sp_buthp_compute(sp_data *sp, sp_buthp *p, SPFLOAT *in, SPFLOAT *out)
{
    if (p->freq <= 0.0) {
        *out = 0;
        return SP_OK;
    }

    if (p->freq != p->lfreq) {
        SPFLOAT *a, c;
        a = p->a;
        p->lfreq = p->freq;
        /* derive C constant used in BLT */
        c = tan((SPFLOAT)(p->pidsr * p->freq));

        /* perform BLT, store components */
        a[0] = 1.0 / (1.0 + c*ROOT2 + c*c);
        a[1] = -2*a[0];
        a[2] = a[0];
        a[3] = 2.0 * (c*c - 1.0) * a[0];
        a[4] = (1.0 - c*ROOT2 + c*c) * a[0];
    }

    filter(in, out, p->a);
    return SP_OK;
}
