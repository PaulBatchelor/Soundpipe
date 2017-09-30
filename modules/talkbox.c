/*
 * Foo
 * 
 * This is a dummy module. It doesn't do much.
 * Feel free to use this as a boilerplate template.
 * 
 */

#include <stdlib.h>
#include "soundpipe.h"

int sp_talkbox_create(sp_talkbox **p)
{
    *p = malloc(sizeof(sp_talkbox));
    return SP_OK;
}

int sp_talkbox_destroy(sp_talkbox **p)
{
    free(*p);
    return SP_OK;
}

int sp_talkbox_init(sp_data *sp, sp_talkbox *p)
{
    /* Initalize variables here. */
    p->bar = 123;
    return SP_OK;
}

int sp_talkbox_compute(sp_data *sp, sp_talkbox *p, SPFLOAT *in, SPFLOAT *out)
{
    /* Send the signal's input to the output */
    *out = *in;
    return SP_OK;
}
