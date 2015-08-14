#include <stdlib.h>
#include "soundpipe.h"

int sp_count_create(sp_count **p)
{
    *p = malloc(sizeof(sp_count));
    return SP_OK;
}

int sp_count_destroy(sp_count **p)
{
    free(*p);
    return SP_OK;
}

int sp_count_init(sp_data *sp, sp_count *p)
{
    p->count = 4;
    p->curcount = -1;
    return SP_OK;
}

int sp_count_compute(sp_data *sp, sp_count *p, SPFLOAT *in, SPFLOAT *out)
{
    int i;
    if(*in){
        p->curcount = (p->curcount + 1) % p->count;
    }
    *out = p->curcount;
    return SP_OK;
}
