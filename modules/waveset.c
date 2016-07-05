/*
 * Foo
 * 
 * This is a dummy module. It doesn't do much.
 * Feel free to use this as a boilerplate template.
 * 
 */

#include <stdlib.h>
#include "soundpipe.h"

int sp_waveset_create(sp_waveset **p)
{
    *p = malloc(sizeof(sp_waveset));
    return SP_OK;
}

int sp_waveset_destroy(sp_waveset **p)
{
    free(*p);
    return SP_OK;
}

int sp_waveset_init(sp_data *sp, sp_waveset *p)
{
    /* Initalize variables here. */
    p->bar = 123;
    return SP_OK;
}

int sp_waveset_compute(sp_data *sp, sp_waveset *p, SPFLOAT *in, SPFLOAT *out)
{
    /* Send the signal's input to the output */
    *out = *in;
    return SP_OK;
}
