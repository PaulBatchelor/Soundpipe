#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "soundpipe.h"

int sp_create(sp_data **spp) {
    *spp = (sp_data *) malloc(sizeof(sp_data));
    sp_data *sp = *spp;
    sprintf(sp->filename, "test.wav");
    sp->out = 0;
    sp->sr = 44100;
    sp->len = 5 * sp->sr;
    return 0;
}

int sp_destroy(sp_data **spp) {
    free(*spp);
    return 0;
}

int sp_process(sp_data *sp, void *ud, void (*callback)(sp_data *, void *)) {
    SF_INFO info;
    info.samplerate = sp->sr;
    info.channels = 1;
    info.format = SF_FORMAT_WAV | SF_FORMAT_FLOAT;
    int numsamps, i;

    sp->sf = sf_open(sp->filename, SFM_WRITE, &info);

    while(sp->len > 0) {
        if(sp->len < SP_BUFSIZE) {
            numsamps = sp->len;
        }else{
            numsamps = SP_BUFSIZE;
        }
        for(i = 0; i < numsamps; i++){
            callback(sp, ud);
            sp->buf[i] = sp->out;
        }
        sf_write_float(sp->sf, sp->buf, numsamps);
        sp->len -= numsamps;
    }
    sf_close(sp->sf);
}
