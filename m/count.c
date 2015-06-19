#include <stdlib.h>
#include "soundpipe.h"

int sp_count_create(sp_count **p)
{
    *p = malloc(sizeof(sp_count));
    return SP_OK;
}

int sp_count_destroy(sp_count **p)
{
    sp_count *pp = *p;
    sp_ftbl_destroy(&pp->c);
    free(*p);
    return SP_OK;
}

int sp_count_init(sp_data *sp, sp_count *p, SPFLOAT count)
{
    p->count = (int32_t) count;
    p->curcount = -1;
    sp_ftbl_create(sp, &p->c, p->count);
    return SP_OK;
}

int sp_count_compute(sp_data *sp, sp_count *p, SPFLOAT *in, SPFLOAT *out)
{
    int i;
    for(i = 0; i < p->c->size; i++) p->c->tbl[i] = 0;
    if(*in){
        p->curcount = (p->curcount + 1) % p->count;
        p->c->tbl[p->curcount] = 1.0;
    }
    *out = p->curcount;
    return SP_OK;
}
