/*
 * Foo
 * 
 * This is a dummy module. It doesn't do much.
 * Feel free to use this as a boilerplate template.
 * 
 */

#include <stdlib.h>
#include "soundpipe.h"

int sp_fog_create(sp_fog **p)
{
    *p = malloc(sizeof(sp_fog));
    return SP_OK;
}

int sp_fog_destroy(sp_fog **p)
{
    free(*p);
    return SP_OK;
}

int sp_fog_init(sp_data *sp, sp_fog *p)
{
    /* Initalize variables here. */
    p->bar = 123;
    return SP_OK;
}

int sp_fog_compute(sp_data *sp, sp_fog *p, SPFLOAT *in, SPFLOAT *out)
{
    /* Send the signal's input to the output */
    *out = *in;
    return SP_OK;
}
