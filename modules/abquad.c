#include <stdlib.h>
#include <math.h>
#include "soundpipe.h"

int sp_abquad_create(sp_abquad **p)
{
		*p = malloc(sizeof(sp_abquad));
		return SP_OK;
}

int sp_abquad_destroy(sp_abquad **p)
{
		free(*p);
		return SP_OK;
}

int sp_abquad_init(sp_data* sp, sp_abquad* p)
{
		p->b0 = 0;
		p->b1 = 0;
		p->b2 = 0;
		p->a1 = 0;
		p->a2 = 0;
		p->z1 = 0;
		p->z2 = 0;
		return SP_OK;
}

int sp_abquad_compute(sp_data* sp, sp_abquad* p, SPFLOAT *input, SPFLOAT* output)
{
		SPFLOAT in = *input;
	  *output = p->z1 + in * p->b0;
	  p->z1 = p->z2 + in * p->b1 - *output*p->a1;
	  p->z2 = in * p->b2 - *output*p->a2;
		return SP_OK;
}

int sp_abquad_set(sp_data* sp, sp_abquad* p, const SPFLOAT coefs[5])
{
		p->b0 = coefs[0];
		p->b1 = coefs[1];
		p->b2 = coefs[2];
		p->a1 = coefs[3];
		p->a2 = coefs[4];
		return SP_OK;
}

