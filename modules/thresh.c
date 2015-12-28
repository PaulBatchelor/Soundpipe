/*
 * Foo
 * 
 * This is a dummy module. It doesn't do much.
 * Feel free to use this as a boilerplate template.
 * 
 */

#include <stdlib.h>
#include "soundpipe.h"

int sp_thresh_create(sp_thresh **p)
{
    *p = malloc(sizeof(sp_thresh));
    return SP_OK;
}

int sp_thresh_destroy(sp_thresh **p)
{
    free(*p);
    return SP_OK;
}

int sp_thresh_init(sp_data *sp, sp_thresh *p)
{
    /* Initalize variables here. */
    p->bar = 123;
    return SP_OK;
}

int sp_thresh_compute(sp_data *sp, sp_thresh *p, SPFLOAT *in, SPFLOAT *out)
{
    /* Send the signal's input to the output */
    *out = *in;
    return SP_OK;
}
