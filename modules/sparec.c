#include <stdlib.h>
#include "soundpipe.h"

#define SPA_BUFSIZE 4096

int sp_sparec_create(sp_sparec **p)
{
    *p = malloc(sizeof(sp_sparec));
    return SP_OK;
}

int sp_sparec_destroy(sp_sparec **p)
{
    sp_sparec *pp = *p;
    sp_auxdata_free(&pp->aux);
    spa_close(&pp->spa);
    free(*p);
    return SP_OK;
}

int sp_sparec_init(sp_data *sp, sp_sparec *p, const char *filename)
{
    if(spa_open(sp, &p->spa, filename, SPA_WRITE) != SP_OK) {
        return SP_NOT_OK;
    }
    
    p->pos = SPA_BUFSIZE;

    p->bufsize = SPA_BUFSIZE;
    sp_auxdata_alloc(&p->aux, sizeof(SPFLOAT) * p->bufsize);

    p->buf = p->aux.ptr;
    return SP_OK;
}

int sp_sparec_compute(sp_data *sp, sp_sparec *p, SPFLOAT *in, SPFLOAT *out)
{
    if(p->pos == 0) {
        p->pos = p->bufsize;
        spa_write_buf(sp, &p->spa, p->buf, p->bufsize);
    }

    p->buf[p->bufsize - p->pos] = *in;

    p->pos--;
    *out = *in;
    return SP_OK;
}

/* call this to close sparec. will write the rest of the buffer */
int sp_sparec_close(sp_data *sp, sp_sparec *p)
{
    if(p->pos < p->bufsize - 1) {
        spa_write_buf(sp, &p->spa, p->buf, p->bufsize - p->pos);
    }
    return SP_OK;
}
