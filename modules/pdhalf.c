/*
 * Foo
 * 
 * This is a dummy module. It doesn't do much.
 * Feel free to use this as a boilerplate template.
 * 
 */

#include <stdlib.h>
#include "soundpipe.h"

int sp_pdhalf_create(sp_pdhalf **p)
{
    *p = malloc(sizeof(sp_pdhalf));
    return SP_OK;
}

int sp_pdhalf_destroy(sp_pdhalf **p)
{
    free(*p);
    return SP_OK;
}

int sp_pdhalf_init(sp_data *sp, sp_pdhalf *p)
{
    /* Initalize variables here. */
    p->bar = 123;
    return SP_OK;
}

int sp_pdhalf_compute(sp_data *sp, sp_pdhalf *p, SPFLOAT *in, SPFLOAT *out)
{
    /* Send the signal's input to the output */
    *out = *in;
    return SP_OK;
}
