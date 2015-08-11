#include <stdlib.h>
#include "soundpipe.h"

int sp_delay_create(sp_delay **p)
{
    *p = malloc(sizeof(sp_delay));
    return SP_OK;
}

int sp_delay_destroy(sp_delay **p)
{
    sp_delay *pp = *p;
    sp_auxdata_free(&pp->buf);
    free(*p);
    return SP_OK;
}

int sp_delay_init(sp_data *sp, sp_delay *p, SPFLOAT time)
{
    p->time = time;
    p->bufsize = time * sp->sr + 1;
    sp_auxdata_alloc(&p->buf, p->bufsize * sizeof(SPFLOAT));
    p->init = 1;
    p->bufpos = 0;
    return SP_OK;
}

int sp_delay_compute(sp_data *sp, sp_delay *p, SPFLOAT *in, SPFLOAT *out)
{
    if(p->init) {
        *out = 0;
        sp_auxdata_setbuf(&p->buf, p->bufpos, in);
        p->bufpos++;
        if(p->bufpos > p->bufsize - 1) p->init = 0;
        p->bufpos %= p->bufsize;
    } else {
        sp_auxdata_getbuf(&p->buf, p->bufpos, out);
        sp_auxdata_setbuf(&p->buf, p->bufpos, in);
        p->bufpos++;
        p->bufpos %= p->bufsize;
    }
    return SP_OK;
}
