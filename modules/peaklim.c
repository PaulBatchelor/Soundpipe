/*
 * Foo
 * 
 * This is a dummy module. It doesn't do much.
 * Feel free to use this as a boilerplate template.
 * 
 */

#include <stdlib.h>
#include "soundpipe.h"

int sp_peaklim_create(sp_peaklim **p)
{
    *p = malloc(sizeof(sp_peaklim));
    return SP_OK;
}

int sp_peaklim_destroy(sp_peaklim **p)
{
    free(*p);
    return SP_OK;
}

int sp_peaklim_init(sp_data *sp, sp_peaklim *p)
{
    /* Initalize variables here. */
    p->bar = 123;
    return SP_OK;
}

int sp_peaklim_compute(sp_data *sp, sp_peaklim *p, SPFLOAT *in, SPFLOAT *out)
{
    /* Send the signal's input to the output */
    *out = *in;
    return SP_OK;
}
