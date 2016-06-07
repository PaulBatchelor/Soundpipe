/*
 * Foo
 * 
 * This is a dummy module. It doesn't do much.
 * Feel free to use this as a boilerplate template.
 * 
 */

#include <stdlib.h>
#include "soundpipe.h"

int sp_clockdiv_create(sp_clockdiv **p)
{
    *p = malloc(sizeof(sp_clockdiv));
    return SP_OK;
}

int sp_clockdiv_destroy(sp_clockdiv **p)
{
    free(*p);
    return SP_OK;
}

int sp_clockdiv_init(sp_data *sp, sp_clockdiv *p)
{
    /* Initalize variables here. */
    p->bar = 123;
    return SP_OK;
}

int sp_clockdiv_compute(sp_data *sp, sp_clockdiv *p, SPFLOAT *in, SPFLOAT *out)
{
    /* Send the signal's input to the output */
    *out = *in;
    return SP_OK;
}
