#include <stdlib.h>
#include "soundpipe.h"

int sp_tenv_create(sp_tenv **p)
{
    *p = malloc(sizeof(sp_tenv));
    sp_tenv *pp = *p;
    sp_tevent_create(&pp->te);
    return SP_OK;
}

int sp_tenv_destroy(sp_tenv **p)
{
    sp_tenv *pp = *p;
    sp_tevent_destroy(&pp->te);
    free(*p);
    return SP_OK;
}

int sp_tenv_init(sp_data *sp, sp_tenv *p, SPFLOAT atk, SPFLOAT hold, SPFLOAT rel)
{
    p->pos = 0;
    p->last = 0;
    p->atk = atk;
    p->rel = rel;
    p->hold = hold;
    p->rel = rel;

    p->sr = sp->sr;
    p->atk_end = p->sr * atk;
    p->rel_start = p->sr * (atk + hold);
    p->atk_slp = 1.0 / p->atk_end;
    p->rel_slp = -1.0 / (p->sr * p->rel);
    p->totaldur = p->sr * (atk + hold + rel);
    sp_tevent_init(sp, p->te, sp_tenv_reinit, sp_tenv_comp, p);
    return SP_OK;
}

void sp_tenv_reinit(void *ud)
{
    sp_tenv *env = ud;
    env->pos = 0;
    //env->last = 0;
    env->atk_end = env->sr * env->atk;
    env->rel_start = env->sr * (env->atk + env->hold);
    env->atk_slp = 1.0 / env->atk_end;
    env->rel_slp = -1.0 / (env->sr * env->rel);
}

void sp_tenv_comp(void *ud, SPFLOAT *out)
{
    sp_tenv *env = ud;
    uint32_t pos = env->pos;
    *out = 0.0;
    if(pos < env->atk_end){
        *out = env->last + env->atk_slp;
    }else if (pos < env->rel_start){
        *out = 1.0;
    }else if (pos < env->totaldur){
        *out = env->last + env->rel_slp;
    }else{
        *out = 0.0;
    }
    
    *out = (*out > 1.0) ? 1.0 : *out;
    *out = (*out < 0.0) ? 0.0 : *out;
    
    env->pos++;
    env->last = *out;
}

int sp_tenv_compute(sp_data *sp, sp_tenv *p, SPFLOAT *in, SPFLOAT *out)
{
    sp_tevent_compute(sp, p->te, in, out);
    return SP_OK;
}
