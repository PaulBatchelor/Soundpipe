/*
 * Foo
 * 
 * This is a dummy module. It doesn't do much.
 * Feel free to use this as a boilerplate template.
 * 
 */

#include <stdlib.h>
#include "soundpipe.h"

int sp_wpkorg35_create(sp_wpkorg35 **p)
{
    *p = malloc(sizeof(sp_wpkorg35));
    return SP_OK;
}

int sp_wpkorg35_destroy(sp_wpkorg35 **p)
{
    free(*p);
    return SP_OK;
}

int sp_wpkorg35_init(sp_data *sp, sp_wpkorg35 *p)
{
    /* Initalize variables here. */
    p->bar = 123;
    return SP_OK;
}

int sp_wpkorg35_compute(sp_data *sp, sp_wpkorg35 *p, SPFLOAT *in, SPFLOAT *out)
{
    /* Send the signal's input to the output */
    *out = *in;
    return SP_OK;
}
