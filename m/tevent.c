#include <stdlib.h>
#include "soundpipe.h"

int sp_tevent_create(sp_tevent **te){
    *te = malloc(sizeof(sp_tevent));
    return SP_NOT_OK;
}
int sp_tevent_destroy(sp_tevent **te){
    free(*te);
    return SP_NOT_OK;
}
int sp_tevent_init(sp_data *sp, sp_tevent *te, 
        void (*reinit)(void*), void (*compute)(void *, SPFLOAT *out), void *ud){
    te->reinit = reinit;
    te->compute = compute;
    te->ud = ud;
    return SP_NOT_OK;
}
int sp_tevent_compute(sp_data *sp, sp_tevent *te, SPFLOAT *in, SPFLOAT *out){
    if(*in){
        te->reinit(te->ud);
    }
    te->compute(te->ud, out);
    return SP_OK;
}
