#include <stdlib.h>
#include "soundpipe.h"
#include "tinywav.h"

#define WAVOUT_BUFSIZE 1024

struct sp_wavout {
    TinyWav tw; 
    SPFLOAT buf[WAVOUT_BUFSIZE];
    int count;
};

int sp_wavout_create(sp_wavout **p)
{
    *p = malloc(sizeof(sp_wavout));
    return SP_OK;
}

int sp_wavout_destroy(sp_wavout **p)
{
    /* write any remaining samples */
    if((*p)->count != 0) {
        tinywav_write_f(&(*p)->tw, (*p)->buf, (*p)->count);
    }
    /* close the file */
    tinywav_close_write(&(*p)->tw);
    free(*p);
    return SP_OK;
}

int sp_wavout_init(sp_data *sp, sp_wavout *p, const char *filename)
{
    p->count = 0;
    tinywav_open_write(&p->tw, 1, sp->sr, TW_FLOAT32, TW_INLINE, filename);
    return SP_OK;
}

int sp_wavout_compute(sp_data *sp, sp_wavout *p, SPFLOAT *in, SPFLOAT *out)
{
    *out = *in;
    if(p->count == WAVOUT_BUFSIZE) {
        tinywav_write_f(&p->tw, p->buf, WAVOUT_BUFSIZE);
        p->count = 0;
    }
    p->buf[p->count] = *in;
    p->count++;
    return SP_OK;
}
