/*
 * WPKorg35
 * 
 * This is a filter based off of an implemenation the Korg35 filter by Will
 * Pirke. It has been ported from the CCRMA chugin by the same name.
 * 
 */

#include <stdlib.h>
#include "soundpipe.h"

enum{LPF1, HPF1};
enum{OFF, ON};

/* VAOnePoleFilter methods */

static void va_getFeedbackOutput(sp_va_onepole *va)
{

}

static void va_reset(sp_va_onepole *va)
{

}

static void va_updateFilter(sp_va_onepole *va)
{

}

static void va_doFilter(sp_va_onepole *va)
{

}

/* WPKorg35 Methods */

static uint32_t wpk_prepareForPlay(sp_wpkorg35 *wpk)
{
    return 1;
}

static void wpk_updateFilters(sp_wpkorg35 *wpk)
{

}

SPFLOAT wpk_doFilter(sp_wpkorg35 *wpk)
{
    return 0.0;
}

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
    return SP_OK;
}

int sp_wpkorg35_compute(sp_data *sp, sp_wpkorg35 *p, SPFLOAT *in, SPFLOAT *out)
{
    /* Send the signal's input to the output */
    *out = *in;
    return SP_OK;
}
