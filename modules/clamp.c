/*
 * Foo
 * 
 * This is a dummy module. It doesn't do much.
 * Feel free to use this as a boilerplate template.
 * 
 */

#include <stdlib.h>
#include "soundpipe.h"

int sp_clamp_create(sp_clamp **p)
{
    *p = malloc(sizeof(sp_clamp));
    return SP_OK;
}

int sp_clamp_destroy(sp_clamp **p)
{
    free(*p);
    return SP_OK;
}

int sp_clamp_init(sp_data *sp, sp_clamp *p)
{
    /* Initalize variables here. */
    p->bar = 123;
    return SP_OK;
}

int sp_clamp_compute(sp_data *sp, sp_clamp *p, SPFLOAT *in, SPFLOAT *out)
{
    /* Send the signal's input to the output */
    *out = *in;
    return SP_OK;
}
