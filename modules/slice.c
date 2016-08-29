/*
 * Foo
 * 
 * This is a dummy module. It doesn't do much.
 * Feel free to use this as a boilerplate template.
 * 
 */

#include <stdlib.h>
#include "soundpipe.h"

int sp_slice_create(sp_slice **p)
{
    *p = malloc(sizeof(sp_slice));
    return SP_OK;
}

int sp_slice_destroy(sp_slice **p)
{
    free(*p);
    return SP_OK;
}

int sp_slice_init(sp_data *sp, sp_slice *p)
{
    /* Initalize variables here. */
    p->bar = 123;
    return SP_OK;
}

int sp_slice_compute(sp_data *sp, sp_slice *p, SPFLOAT *in, SPFLOAT *out)
{
    /* Send the signal's input to the output */
    *out = *in;
    return SP_OK;
}
