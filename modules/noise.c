#include <math.h>
#include <stdlib.h>
#include "soundpipe.h"

int sp_noise_create(sp_noise **ns)
{
    *ns = malloc(sizeof(sp_noise));
    return SP_OK;
}

int sp_noise_init(sp_data *sp, sp_noise *ns)
{
    ns->gain = 1.0;
    return SP_OK;
}

int sp_noise_compute(sp_data *sp, sp_noise *ns, SPFLOAT *in, SPFLOAT *out)
{
    *out = ((rand() % RAND_MAX) / (RAND_MAX * 1.0));
    *out = (*out * 2) - 1;
    *out *= ns->gain;
    return SP_OK;
}

int sp_noise_destroy(sp_noise **ns)
{
    free(*ns);
    return SP_OK;
}
