/*
 * Foo
 *
 * This is a dummy module. It doesn't do much.
 * Feel free to use this as a boilerplate template.
 *
 */

#include <stdlib.h>
#include "soundpipe.h"

int sp_granule_create(sp_granule **p)
{
    *p = malloc(sizeof(sp_granule));
    return SP_OK;
}

int sp_granule_destroy(sp_granule **p)
{
    free(*p);
    return SP_OK;
}

int sp_granule_init(sp_data *sp, sp_granule *p)
{
    /* Initalize variables here. */
    p->bar = 123;
    return SP_OK;
}

int sp_granule_compute(sp_data *sp, sp_granule *p, SPFLOAT *in, SPFLOAT *out)
{
    /* Send the signal's input to the output */
    *out = *in;
    return SP_OK;
}
