/*
 * Foo
 * 
 * This is a dummy module. It doesn't do much.
 * Feel free to use this as a boilerplate template.
 * 
 */

#include <stdlib.h>
#include "soundpipe.h"

int sp_sdelay_create(sp_sdelay **p)
{
    *p = malloc(sizeof(sp_sdelay));
    return SP_OK;
}

int sp_sdelay_destroy(sp_sdelay **p)
{
    free(*p);
    return SP_OK;
}

int sp_sdelay_init(sp_data *sp, sp_sdelay *p)
{
    /* Initalize variables here. */
    p->bar = 123;
    return SP_OK;
}

int sp_sdelay_compute(sp_data *sp, sp_sdelay *p, SPFLOAT *in, SPFLOAT *out)
{
    /* Send the signal's input to the output */
    *out = *in;
    return SP_OK;
}
