/*
 * Foo
 * 
 * This is a dummy module. It doesn't do much.
 * Feel free to use this as a boilerplate template.
 * 
 */

#include <stdlib.h>
#include "soundpipe.h"

int sp_oscmorph_create(sp_oscmorph **p)
{
    *p = malloc(sizeof(sp_oscmorph));
    return SP_OK;
}

int sp_oscmorph_destroy(sp_oscmorph **p)
{
    free(*p);
    return SP_OK;
}

int sp_oscmorph_init(sp_data *sp, sp_oscmorph *p)
{
    /* Initalize variables here. */
    p->bar = 123;
    return SP_OK;
}

int sp_oscmorph_compute(sp_data *sp, sp_oscmorph *p, SPFLOAT *in, SPFLOAT *out)
{
    /* Send the signal's input to the output */
    *out = *in;
    return SP_OK;
}
