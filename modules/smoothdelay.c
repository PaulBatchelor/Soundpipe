/*
 * Foo
 * 
 * This is a dummy module. It doesn't do much.
 * Feel free to use this as a boilerplate template.
 * 
 */

#include <stdlib.h>
#include "soundpipe.h"

int sp_smoothdelay_create(sp_smoothdelay **p)
{
    *p = malloc(sizeof(sp_smoothdelay));
    return SP_OK;
}

int sp_smoothdelay_destroy(sp_smoothdelay **p)
{
    free(*p);
    return SP_OK;
}

int sp_smoothdelay_init(sp_data *sp, sp_smoothdelay *p)
{
    /* Initalize variables here. */
    p->bar = 123;
    return SP_OK;
}

int sp_smoothdelay_compute(sp_data *sp, sp_smoothdelay *p, SPFLOAT *in, SPFLOAT *out)
{
    /* Send the signal's input to the output */
    *out = *in;
    return SP_OK;
}
