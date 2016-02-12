/*
 * Foo
 * 
 * This is a dummy module. It doesn't do much.
 * Feel free to use this as a boilerplate template.
 * 
 */

#include <stdlib.h>
#include "soundpipe.h"

int sp_fof_create(sp_fof **p)
{
    *p = malloc(sizeof(sp_fof));
    return SP_OK;
}

int sp_fof_destroy(sp_fof **p)
{
    free(*p);
    return SP_OK;
}

int sp_fof_init(sp_data *sp, sp_fof *p)
{
    /* Initalize variables here. */
    p->bar = 123;
    return SP_OK;
}

int sp_fof_compute(sp_data *sp, sp_fof *p, SPFLOAT *in, SPFLOAT *out)
{
    /* Send the signal's input to the output */
    *out = *in;
    return SP_OK;
}
