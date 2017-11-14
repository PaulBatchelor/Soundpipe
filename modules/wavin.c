#include <stdlib.h>
#include "soundpipe.h"
#include "tinywav.h"
#define DR_WAV_IMPLEMENTATION
#include "dr_wav.h"

#define WAVIN_BUFSIZE 1024

struct sp_wavin {
    TinyWav tw; 
    SPFLOAT buf[WAVIN_BUFSIZE];
    int count;
    drwav wav;
};

int sp_wavin_create(sp_wavin **p)
{
    *p = malloc(sizeof(sp_wavin));
    return SP_OK;
}

int sp_wavin_destroy(sp_wavin **p)
{
    /* tinywav_close_read(&(*p)->tw); */
    drwav_uninit(&(*p)->wav);
    free(*p);
    return SP_OK;
}

int sp_wavin_init(sp_data *sp, sp_wavin *p, const char *filename)
{
    p->count = 0;
    /* tinywav_open_read(&p->tw, filename, TW_INTERLEAVED, TW_FLOAT32); */
    drwav_init_file(&p->wav, filename);
    return SP_OK;
}

int sp_wavin_compute(sp_data *sp, sp_wavin *p, SPFLOAT *in, SPFLOAT *out)
{
    if(p->count == 0) {
        drwav_read_f32(&p->wav, WAVIN_BUFSIZE, p->buf);
    }

    *out = p->buf[p->count];
    p->count = (p->count + 1) % WAVIN_BUFSIZE;
    return SP_OK;
}
