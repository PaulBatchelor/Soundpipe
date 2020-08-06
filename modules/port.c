/*
 * Port
 *
 * Port is a one-pole smoothing filter, typically used on
 * control signals to create a "portamenteau" effect.
 *
 * This filter design uses the difference equation:
 *
 * y(n) = b0*x(n) - a1*y(n - 1)
 *
 * Where a1 is (0.5^(1/(t * sr))), and b0 is (1 - a1).
 *
 * More information on one-pole smoothers can be found here:
 * https://ccrma.stanford.edu/~jos/filters/One_Pole.html
 */


#include <math.h>
#include <stdint.h>
#include <stdlib.h>

#include "soundpipe.h"

int sp_port_create(sp_port **p)
{
    *p = malloc(sizeof(sp_port));
    return SP_OK;
}

int sp_port_destroy(sp_port **p)
{
    free(*p);
    return SP_OK;
}

int sp_port_init(sp_data *sp, sp_port *p)
{
    p->y0 = 0;
    p->b0 = 0;
    p->a1 = 0;
    p->psmooth = -100.0;
    p->smooth = 0.01;

    /* using this constant shaves off a multiply operation */
    p->onedsr = 1.0/sp->sr;
    return SP_OK;
}

int sp_port_compute(sp_data *sp, sp_port *p, SPFLOAT *in, SPFLOAT *out)
{
    if (p->psmooth != p->smooth) {
        p->a1 = pow(0.5, p->onedsr/p->smooth);
        p->b0 = 1.0 - p->a1;
        p->psmooth = p->smooth;
    }

    p->y0 = p->b0 * (*in) + p->a1 * p->y0;
    *out = p->y0;
    return SP_OK;
}

int sp_port_reset(sp_data *sp, sp_port *p, SPFLOAT *in)
{
    p->y0 = *in;
    return SP_OK;
}
