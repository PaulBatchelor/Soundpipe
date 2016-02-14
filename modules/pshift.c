/*
 * Foo
 * 
 * This is a dummy module. It doesn't do much.
 * Feel free to use this as a boilerplate template.
 * 
 */

#include <stdlib.h>
#include "soundpipe.h"

int sp_pshift_create(sp_pshift **p)
{
    *p = malloc(sizeof(sp_pshift));
    return SP_OK;
}

int sp_pshift_destroy(sp_pshift **p)
{
    free(*p);
    return SP_OK;
}

int sp_pshift_init(sp_data *sp, sp_pshift *p)
{
    /* Initalize variables here. */
    p->bar = 123;
    return SP_OK;
}

int sp_pshift_compute(sp_data *sp, sp_pshift *p, SPFLOAT *in, SPFLOAT *out)
{
    /* Send the signal's input to the output */
    *out = *in;
    return SP_OK;
}
