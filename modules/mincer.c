/*
 * Foo
 * 
 * This is a dummy module. It doesn't do much.
 * Feel free to use this as a boilerplate template.
 * 
 */

#include <stdlib.h>
#include "soundpipe.h"

int sp_mincer_create(sp_mincer **p)
{
    *p = malloc(sizeof(sp_mincer));
    return SP_OK;
}

int sp_mincer_destroy(sp_mincer **p)
{
    free(*p);
    return SP_OK;
}

int sp_mincer_init(sp_data *sp, sp_mincer *p)
{
    /* Initalize variables here. */
    p->bar = 123;
    return SP_OK;
}

int sp_mincer_compute(sp_data *sp, sp_mincer *p, SPFLOAT *in, SPFLOAT *out)
{
    /* Send the signal's input to the output */
    *out = *in;
    return SP_OK;
}
