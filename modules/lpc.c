/*
 * Foo
 * 
 * This is a dummy module. It doesn't do much.
 * Feel free to use this as a boilerplate template.
 * 
 */

#include <stdlib.h>
#include "soundpipe.h"

int sp_lpc_create(sp_lpc **p)
{
    *p = malloc(sizeof(sp_lpc));
    return SP_OK;
}

int sp_lpc_destroy(sp_lpc **p)
{
    free(*p);
    return SP_OK;
}

int sp_lpc_init(sp_data *sp, sp_lpc *p)
{
    /* Initalize variables here. */
    p->bar = 123;
    return SP_OK;
}

int sp_lpc_compute(sp_data *sp, sp_lpc *p, SPFLOAT *in, SPFLOAT *out)
{
    /* Send the signal's input to the output */
    *out = *in;
    return SP_OK;
}
