/*
 * WPKorg35
 * 
 * This is a filter based off of an implemenation the Korg35 filter by Will
 * Pirke. It has been ported from the CCRMA chugin by the same name.
 * 
 */

#include <stdlib.h>
#include <math.h>
#include "soundpipe.h"

#ifndef M_PI
#define M_PI		3.14159265358979323846
#endif

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
    /* reset memory for filters */
    p->lpf1_z = 0;
    p->lpf2_z = 0;
    p->hpf_z = 0;

    /* update filters */

    
	/* prewarp for BZT */
	SPFLOAT wd = 2*M_PI*p->m_dFC;          
	SPFLOAT T  = 1.0/(SPFLOAT)sp->sr;             
	SPFLOAT wa = (2/T)*tan(wd*T/2); 
	SPFLOAT g  = wa*T/2;    

	/* the feedforward coeff in the VA One Pole */
	SPFLOAT G = g/(1.0 + g);

    p->lpf1_a = G;
    p->lpf2_a = G;
    p->hpf_a = G;

    return SP_OK;
}

int sp_wpkorg35_compute(sp_data *sp, sp_wpkorg35 *p, SPFLOAT *in, SPFLOAT *out)
{
    /* Send the signal's input to the output */
    *out = *in;
    return SP_OK;
}
