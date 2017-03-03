/*
 * Foo
 * 
 * This is a dummy module. It doesn't do much.
 * Feel free to use this as a boilerplate template.
 * 
 */

#include <stdlib.h>
#include "soundpipe.h"

int sp_brown_create(sp_brown **p)
{
    *p = malloc(sizeof(sp_brown));
    return SP_OK;
}

int sp_brown_destroy(sp_brown **p)
{
    free(*p);
    return SP_OK;
}

int sp_brown_init(sp_data *sp, sp_brown *p)
{
    /* Initalize variables here. */
    p->bar = 123;
    return SP_OK;
}

int sp_brown_compute(sp_data *sp, sp_brown *p, SPFLOAT *in, SPFLOAT *out)
{
    /* Send the signal's input to the output */
    *out = *in;
    return SP_OK;
}
