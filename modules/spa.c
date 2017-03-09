#include <stdlib.h>
#include "soundpipe.h"

#define SPA_BUFSIZE 4096

int sp_spa_create(sp_spa **p)
{
    *p = malloc(sizeof(sp_spa));
    return SP_OK;
}

int sp_spa_destroy(sp_spa **p)
{
    sp_spa *pp = *p;
    sp_auxdata_free(&pp->aux);
    spa_close(&pp->spa);
    free(*p);
    return SP_OK;
}

int sp_spa_init(sp_data *sp, sp_spa *p, const char *filename)
{
    if(spa_open(sp, &p->spa, filename, SPA_READ) != SP_OK) {
        return SP_NOT_OK;
    }
    
    p->pos = 0;

    p->bufsize = SPA_BUFSIZE;
    sp_auxdata_alloc(&p->aux, sizeof(SPFLOAT) * p->bufsize);

    p->buf = p->aux.ptr;

    return SP_OK;
}

int sp_spa_compute(sp_data *sp, sp_spa *p, SPFLOAT *in, SPFLOAT *out)
{
    if(p->bufsize == 0) {
        *out = 0.0;
        return SP_OK;
    }

    if(p->pos == 0) {
        p->bufsize = spa_read_buf(sp, &p->spa, p->buf, SPA_BUFSIZE);
        if(p->bufsize == 0) {
            *out = 0.0;
            return SP_OK;
        }
    }

    *out = p->buf[p->pos];
    p->pos = (p->pos + 1) % p->bufsize;
    return SP_OK;
}
