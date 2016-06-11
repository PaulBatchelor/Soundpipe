/*
 * Foo
 * 
 * This is a dummy module. It doesn't do much.
 * Feel free to use this as a boilerplate template.
 * 
 */

#include <stdlib.h>
#include "soundpipe.h"

int sp_hilbert_create(sp_hilbert **p)
{
    *p = malloc(sizeof(sp_hilbert));
    return SP_OK;
}

int sp_hilbert_destroy(sp_hilbert **p)
{
    free(*p);
    return SP_OK;
}

int sp_hilbert_init(sp_data *sp, sp_hilbert *p)
{
    /* Initalize variables here. */
    p->bar = 123;
    return SP_OK;
}

int sp_hilbert_compute(sp_data *sp, sp_hilbert *p, SPFLOAT *in, SPFLOAT *out)
{
    /* Send the signal's input to the output */
    *out = *in;
    return SP_OK;
}
