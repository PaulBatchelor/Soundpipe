#include <stdlib.h>
#include "soundpipe.h"

int sp_spa_create(sp_spa **p)
{
    *p = malloc(sizeof(sp_spa));
    return SP_OK;
}

int sp_spa_destroy(sp_spa **p)
{
    free(*p);
    return SP_OK;
}

int sp_spa_init(sp_data *sp, sp_spa *p, const char *filename)
{
    return SP_OK;
}

int sp_spa_compute(sp_data *sp, sp_spa *p, SPFLOAT *in, SPFLOAT *out)
{
    *out = *in;
    return SP_OK;
}
