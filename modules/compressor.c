/*
 * Foo
 * 
 * This is a dummy module. It doesn't do much.
 * Feel free to use this as a boilerplate template.
 * 
 */

#include <stdlib.h>
#include "soundpipe.h"

int sp_compressor_create(sp_compressor **p)
{
    *p = malloc(sizeof(sp_compressor));
    return SP_OK;
}

int sp_compressor_destroy(sp_compressor **p)
{
    free(*p);
    return SP_OK;
}

int sp_compressor_init(sp_data *sp, sp_compressor *p)
{
    /* Initalize variables here. */
    p->bar = 123;
    return SP_OK;
}

int sp_compressor_compute(sp_data *sp, sp_compressor *p, SPFLOAT *in, SPFLOAT *out)
{
    /* Send the signal's input to the output */
    *out = *in;
    return SP_OK;
}
