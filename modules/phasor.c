/*
 * Phasor
 *
 * A phasor produces a non-bandlimited sawtooth wave,
 * normalized to be in range 0-1. Phasors are most
 * frequently used to create table-lookup oscillators.
 */

#include <stdlib.h>
#include "soundpipe.h"

int sp_phasor_create(sp_phasor **p)
{
    *p = malloc(sizeof(sp_phasor));
    return SP_OK;
}

int sp_phasor_destroy(sp_phasor **p)
{
    free(*p);
    return SP_OK;
}

int sp_phasor_init(sp_data *sp, sp_phasor *p, SPFLOAT iphs)
{
    p->freq = 440;
    p->phs = iphs;
    p->onedsr = 1.0 / sp->sr;
    return SP_OK;
}

int sp_phasor_compute(sp_data *sp, sp_phasor *p, SPFLOAT *in, SPFLOAT *out)
{
    SPFLOAT phs;
    SPFLOAT incr;

    phs = p->phs;
    incr = p->freq * p->onedsr;

    *out = phs;

    phs += incr;

    if (phs >= 1.0) {
        phs -= 1.0;
    } else if (phs < 0.0) {
        phs += 1.0;
    }

    p->phs = phs;
    return SP_OK;
}
