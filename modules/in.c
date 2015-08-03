/*
 * Foo
 * 
 * This is a dummy module. It doesn't do much.
 * Feel free to use this as a boilerplate template.
 * 
 */

#include <stdlib.h>
#include "soundpipe.h"

int sp_in_create(sp_in **p)
{
    *p = malloc(sizeof(sp_in));
    return SP_OK;
}

int sp_in_destroy(sp_in **p)
{
    free(*p);
    return SP_OK;
}

int sp_in_init(sp_data *sp, sp_in *p)
{
    /* Nothing needed here for now */
    return SP_OK;
}

int sp_in_compute(sp_data *sp, sp_in *p, SPFLOAT *in, SPFLOAT *out)
{
    *out = 0;
    fread(out, sizeof(SPFLOAT), 1, stdin);
    return SP_OK;
}
