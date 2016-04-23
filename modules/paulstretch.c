/*
 * Foo
 * 
 * This is a dummy module. It doesn't do much.
 * Feel free to use this as a boilerplate template.
 * 
 */

#include <stdlib.h>
#include "soundpipe.h"

int sp_paulstretch_create(sp_paulstretch **p)
{
    *p = malloc(sizeof(sp_paulstretch));
    return SP_OK;
}

int sp_paulstretch_destroy(sp_paulstretch **p)
{
    free(*p);
    return SP_OK;
}

int sp_paulstretch_init(sp_data *sp, sp_paulstretch *p)
{
    /* Initalize variables here. */
    p->bar = 123;
    return SP_OK;
}

int sp_paulstretch_compute(sp_data *sp, sp_paulstretch *p, SPFLOAT *in, SPFLOAT *out)
{
    /* Send the signal's input to the output */
    *out = *in;
    return SP_OK;
}
