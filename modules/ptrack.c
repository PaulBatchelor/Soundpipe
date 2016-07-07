/*
 * Foo
 * 
 * This is a dummy module. It doesn't do much.
 * Feel free to use this as a boilerplate template.
 * 
 */

#include <stdlib.h>
#include "soundpipe.h"

int sp_ptrack_create(sp_ptrack **p)
{
    *p = malloc(sizeof(sp_ptrack));
    return SP_OK;
}

int sp_ptrack_destroy(sp_ptrack **p)
{
    free(*p);
    return SP_OK;
}

int sp_ptrack_init(sp_data *sp, sp_ptrack *p)
{
    /* Initalize variables here. */
    p->bar = 123;
    return SP_OK;
}

int sp_ptrack_compute(sp_data *sp, sp_ptrack *p, SPFLOAT *in, SPFLOAT *out)
{
    /* Send the signal's input to the output */
    *out = *in;
    return SP_OK;
}
