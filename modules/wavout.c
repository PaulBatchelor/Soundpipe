/*
 * Foo
 * 
 * This is a dummy module. It doesn't do much.
 * Feel free to use this as a boilerplate template.
 * 
 */

#include <stdlib.h>
#include "soundpipe.h"

int sp_wavout_create(sp_wavout **p)
{
    *p = malloc(sizeof(sp_wavout));
    return SP_OK;
}

int sp_wavout_destroy(sp_wavout **p)
{
    free(*p);
    return SP_OK;
}

int sp_wavout_init(sp_data *sp, sp_wavout *p)
{
    /* Initalize variables here. */
    p->bar = 123;
    return SP_OK;
}

int sp_wavout_compute(sp_data *sp, sp_wavout *p, SPFLOAT *in, SPFLOAT *out)
{
    /* Send the signal's input to the output */
    *out = *in;
    return SP_OK;
}
