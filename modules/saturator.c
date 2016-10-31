#include <stdlib.h>
#include <math.h>
#include "soundpipe.h"

#ifndef M_PI
#define M_PI    3.14159265358979323846
#endif

const static SPFLOAT AACoefs[6][7] =
{
    {2.60687e-05, 2.98697e-05, 2.60687e-05, -1.31885, 0.437162, 0.0, 0.0},
    {1, -0.800256, 1, -1.38301, 0.496576, 0.0, 0.0},
    {1, -1.42083, 1, -1.48787, 0.594413, 0.0, 0.0},
    {1, -1.6374, 1, -1.60688, 0.707142, 0.0, 0.0},
    {1, -1.7261, 1, -1.7253, 0.822156, 0.0, 0.0},
    {1, -1.75999, 1, -1.84111, 0.938811, 0.0, 0.0}
};

static void bilinearTranform(SPFLOAT acoefs[], SPFLOAT dcoefs[], SPFLOAT fs)
{
  	SPFLOAT b0, b1, b2, a0, a1, a2;
  	SPFLOAT bz0, bz1, bz2, az0, az1, az2;

  	b0 = acoefs[0]; b1 = acoefs[1]; b2 = acoefs[2];
    a0 = acoefs[3]; a1 = acoefs[4]; a2 = acoefs[5];

  	bz0 = 1.0; bz1 = 0.0; bz2 = 0.0;
    az0 = 1.0; az1 = 0.0; az2 = 0.0;

  	az0 = a2*4*fs*fs + a1*2*fs + a0;

    bz2 = (b2*4*fs*fs - b1*2*fs + b0) / az0;
    bz1 = (-b2*8*fs*fs + 2*b0) / az0;
    bz0 = (b2*4*fs*fs+ b1*2*fs + b0) / az0;
    az2 = (a2*4*fs*fs - a1*2*fs + a0) / az0;
    az1 = (-a2*8*fs*fs + 2*a0) / az0;

	  dcoefs[0] = bz0; dcoefs[1] = bz1; dcoefs[2] = bz2;
    dcoefs[3] = az1; dcoefs[4] = az2;
}

int sp_saturator_create(sp_saturator **p)
{
		*p = malloc(sizeof(sp_saturator));
		return SP_OK;
}

int sp_saturator_destroy(sp_saturator **p)
{
    free(*p);
    return SP_OK;
}

int sp_saturator_init(sp_data *sp, sp_saturator *p)
{
		int i, j;
    SPFLOAT wc_dc = 5*2*M_PI;
    SPFLOAT Scoeffs[6] = {  0, 1, 0, wc_dc, 1, 0 };
    SPFLOAT Zcoeffs[5];
		p->drive = 1;
    p->dcOffset = 0;

    for(i = 0; i < 6; i++){
	    for(j = 0; j < 7; j++){
				p->AAFilter[i][j] =  AACoefs[i][j];
				p->AIFilter[i][j] =  AACoefs[i][j];
	    }
		}
    bilinearTranform(Scoeffs, Zcoeffs, sp->sr*kUSRatio);
    for(i = 0; i < 2; i++){
			for(j = 0; j < 5; j++){
				p->dcBlocker[i][j] = Zcoeffs[j];
			}
			p->dcBlocker[i][5] = 0.0;
			p->dcBlocker[i][6] = 0.0;
		}
		return SP_OK;
}

static int quad_compute(SPFLOAT p[7],  SPFLOAT *input, SPFLOAT* output)
{
    SPFLOAT in = *input;
    *output = p[5] + in * p[0];
    p[5] = p[6] + in * p[1] - *output*p[3];
    p[6] = in * p[2] - *output*p[4];
    return SP_OK;
}


int sp_saturator_compute(sp_data *sp, sp_saturator *p, SPFLOAT *in, SPFLOAT *out)
{
    int i, j;
		SPFLOAT fsignal, usignal, dsignal;

    fsignal = p->drive * *in;
    for(i = 0; i < kUSRatio; i++){
				usignal = (i == 0) ? 8 *fsignal : 0.0;
      	for(j = 0; j < 6; j++){
						quad_compute(p->AIFilter[j], &usignal, &usignal);
				}
        dsignal = (usignal + p->dcOffset) / (1.0 + fabs(usignal + p->dcOffset));

				quad_compute(p->dcBlocker[0], &dsignal, &dsignal);
				quad_compute(p->dcBlocker[1], &dsignal, &dsignal);

      	for(j = 0; j < 6; j++){
					quad_compute(p->AAFilter[j], &dsignal, out);
				}
    }
		return SP_OK;
}
