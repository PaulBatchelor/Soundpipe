/*
 * Foo
 * 
 * This is a dummy module. It doesn't do much.
 * Feel free to use this as a boilerplate template.
 * 
 */

#include <stdlib.h>
#include "soundpipe.h"

int sp_randh_create(sp_randh **p)
{
    *p = malloc(sizeof(sp_randh));
    return SP_OK;
}

int sp_randh_destroy(sp_randh **p)
{
    free(*p);
    return SP_OK;
}

int sp_randh_init(sp_data *sp, sp_randh *p)
{
    /* Initalize variables here. */
    p->bar = 123;
    return SP_OK;
}

int sp_randh_compute(sp_data *sp, sp_randh *p, SPFLOAT *in, SPFLOAT *out)
{
    /* Send the signal's input to the output */
    *out = *in;
    return SP_OK;
}
