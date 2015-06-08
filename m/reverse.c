#include <string.h>
#include <stdlib.h>
#include "soundpipe.h"

/*TODO: merge alloc and create functions together somehow */
int sp_reverse_alloc(sp_data *sp, sp_auxdata *aux, SPFLOAT delay, uint32_t *bufsize){
    size_t size = delay * sp->sr * sizeof(SPFLOAT) * 2;
    *bufsize = size;
    sp_auxdata_alloc(aux, size);
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

int sp_reverse_init(sp_data *sp, sp_reverse *p, sp_auxdata *aux, uint32_t bufsize){
    p->bufpos = 0;
    p->bufsize = aux->size / sizeof(SPFLOAT);    
    p->buf = aux;
    return SP_OK;
}

int sp_reverse_compute(sp_data *sp, sp_reverse *p, SPFLOAT *in, SPFLOAT *out){
    sp_auxdata_getbuf(p->buf, p->bufpos, out);
    sp_auxdata_setbuf(p->buf, (p->bufsize - 1) - p->bufpos, in);
    p->bufpos = (p->bufpos + 1) % p->bufsize;
    return SP_OK;
}
