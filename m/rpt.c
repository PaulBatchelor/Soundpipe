#include <stdlib.h>
#include "soundpipe.h"

int sp_rpt_create(sp_rpt **p){
    *p = malloc(sizeof(sp_rpt));
    return SP_OK;
}

int sp_rpt_destroy(sp_rpt **p){
    sp_rpt *pp = *p;
    sp_auxdata_free(&pp->aux);
    free(*p);
    return SP_OK;
}

int sp_rpt_init(sp_data *sp, sp_rpt *p, SPFLOAT maxdur){
    sp_auxdata_alloc(&p->aux, sizeof(SPFLOAT) * (uint32_t)maxdur);
    p->playpos = 0;
    p->bufpos = 0;
    p->running = 0;
    p->reps = 4;
    p->count = p->reps;
    p->size = p->aux.size;
    p->onedsr = 1.0 / sp->sr;
    return SP_OK;
}

int sp_rpt_compute(sp_data *sp, sp_rpt *p, SPFLOAT *trig, 
        SPFLOAT *in, SPFLOAT *out){
    if(*trig){
        p->running = 1;
        p->playpos = 0;
        p->bufpos = 0;    
        p->count = p->reps;
    }
    if(p->bufpos * sizeof(SPFLOAT) < p->aux.size){
       sp_auxdata_setbuf(&p->aux, p->bufpos, in);
       p->bufpos++;
    }
    if(p->running && p->count > 0){
        if(p->playpos == 0){
            p->count--;
        }
        sp_auxdata_getbuf(&p->aux, p->playpos, out);
        p->playpos = (p->playpos + 1) % p->size;
        p->count--;
    }else{
        *out = *in;
    }
    return SP_OK;
}
int sp_rpt_set(sp_rpt *p, int bpm, int beat, int rep){
    uint32_t size = (beat * (60.0/bpm)) * p->onedsr;
    p->reps = rep;
    if(size * sizeof(SPFLOAT) > p->aux.size){
        fprintf(stderr, "Error: not enough memory allocated for buffer.\n");
        return SP_NOT_OK;
    }else{
        p->size = size;
    }
    return SP_OK;
}
