/*
 * Metro
 *
 * Metro produces a signal steady sequence of impulses,
 * which is typically used as a clock signal to for other
 * modules.
 *
 * Metro is very similar to the "metro" object in puredata,
 * except that the rate parameter unit is supplied in Hz,
 * not ms.
 */

#include <stdlib.h>
#include "soundpipe.h"

int sp_metro_create(sp_metro **p)
{
    *p = malloc(sizeof(sp_metro));
    return SP_OK;
}

int sp_metro_destroy(sp_metro **p)
{
    free(*p);
    return SP_OK;
}

int sp_metro_init(sp_data *sp, sp_metro *p)
{
    p->freq = 2.0;
    p->phs = 0;
    p->init = 1;
    p->onedsr = 1.0 / sp->sr;
    return SP_OK;
}

int sp_metro_compute(sp_data *sp, sp_metro *p, SPFLOAT *in, SPFLOAT *out)
{
    SPFLOAT phs;

    phs = p->phs;

    *out = 0;

    if (p->init) {
        *out = 1.0;
        p->init = 0;
    } else {
        phs += p->freq * p->onedsr;

        if (phs >= 1) {
            *out = 1.0;
            phs -= 1.0;
        }
    }

    p->phs = phs;

    return SP_OK;
}
