/*
 * Foo
 * 
 * This is a dummy module. It doesn't do much.
 * Feel free to use this as a boilerplate template.
 * 
 */

#include <stdlib.h>
#include "soundpipe.h"

int sp_sparec_create(sp_sparec **p)
{
    *p = malloc(sizeof(sp_sparec));
    return SP_OK;
}

int sp_sparec_destroy(sp_sparec **p)
{
    free(*p);
    return SP_OK;
}

int sp_sparec_init(sp_data *sp, sp_sparec *p)
{
    /* Initalize variables here. */
    p->bar = 123;
    return SP_OK;
}

int sp_sparec_compute(sp_data *sp, sp_sparec *p, SPFLOAT *in, SPFLOAT *out)
{
    /* Send the signal's input to the output */
    *out = *in;
    return SP_OK;
}
