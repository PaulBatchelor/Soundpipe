/*
 * Foo
 * 
 * This is a dummy module. It doesn't do much.
 * Feel free to use this as a boilerplate template.
 * 
 */

#include <stdlib.h>
#include "soundpipe.h"

int sp_tblrec_create(sp_tblrec **p)
{
    *p = malloc(sizeof(sp_tblrec));
    return SP_OK;
}

int sp_tblrec_destroy(sp_tblrec **p)
{
    free(*p);
    return SP_OK;
}

int sp_tblrec_init(sp_data *sp, sp_tblrec *p)
{
    /* Initalize variables here. */
    p->bar = 123;
    return SP_OK;
}

int sp_tblrec_compute(sp_data *sp, sp_tblrec *p, SPFLOAT *in, SPFLOAT *out)
{
    /* Send the signal's input to the output */
    *out = *in;
    return SP_OK;
}
