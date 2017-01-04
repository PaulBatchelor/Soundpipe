/*
 * Diode
 * 
 * Based on Will Pirkle's Diode Ladder filter design. 
 * Code adapted from the CCRMA Chugin WPDiodeLadder
 * 
 */

#include <stdlib.h>
#include "soundpipe.h"

int sp_diode_create(sp_diode **p)
{
    *p = malloc(sizeof(sp_diode));
    return SP_OK;
}

int sp_diode_destroy(sp_diode **p)
{
    free(*p);
    return SP_OK;
}

int sp_diode_init(sp_data *sp, sp_diode *p)
{
    /* Initalize variables here. */
    p->bar = 123;
    return SP_OK;
}

int sp_diode_compute(sp_data *sp, sp_diode *p, SPFLOAT *in, SPFLOAT *out)
{
    /* Send the signal's input to the output */
    *out = *in;
    return SP_OK;
}
