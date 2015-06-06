#include <string.h>
#include <stdlib.h>
#include "soundpipe.h"

static int sp_auxdata_getbuf(sp_auxdata *aux, uint32_t pos, SPFLOAT *out){
    if(pos * sizeof(SPFLOAT) > aux->size){
        fprintf(stderr, "Error: Buffer overflow!\n");
        *out = 0;
        return SP_NOT_OK;
    }else{
        SPFLOAT *tmp = aux->ptr; 
        *out = tmp[pos];
    }
    return SP_OK;

}
static int sp_auxdata_setbuf(sp_auxdata *aux, uint32_t pos, SPFLOAT *in){
    if(pos * sizeof(SPFLOAT) > aux->size){
        fprintf(stderr, "Error: Buffer overflow!\n");
        return SP_NOT_OK;
    }else{
        SPFLOAT *tmp = aux->ptr; 
        tmp[pos] = *in;
    }
    return SP_OK;
}

/*TODO: merge alloc and create functions together somehow */
int sp_reverse_alloc(sp_data *sp, sp_auxdata *aux, SPFLOAT delay){
    sp_auxdata_alloc(aux, delay * sp->sr * sizeof(SPFLOAT) * 2);
    return SP_OK;
}

int sp_reverse_create(sp_data *sp, sp_reverse **p){
    *p = malloc(sizeof(sp_reverse));
    return SP_OK;
}

int sp_reverse_destroy(sp_reverse **p, sp_auxdata *aux){
    sp_auxdata_free(aux);
    free(*p);
    return SP_OK;
}

int sp_reverse_init(sp_data *sp, sp_reverse *p, sp_auxdata *aux){
    p->bufpos = 0;
    p->bufsize = aux->size / sizeof(SPFLOAT);    
    p->buf = aux;
    //memset(p->buf->ptr, 0, aux->size);
    return SP_OK;
}

int sp_reverse_compute(sp_data *sp, sp_reverse *p, SPFLOAT *in, SPFLOAT *out){
    sp_auxdata_getbuf(p->buf, p->bufpos, out);
    sp_auxdata_setbuf(p->buf, p->bufsize - p->bufpos, in);
    p->bufpos = (p->bufpos + 1) % p->bufsize;
    return SP_OK;
}
