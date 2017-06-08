#include <stdlib.h>
#include <stdio.h>
#include "soundpipe.h"
#include "config.h"

int main() {
    sp_data *sp;
    sp_create(&sp);
    sp_srand(sp, 12345);
    sp->sr = SR;
    sp->len = sp->sr * LEN;
    uint32_t t, u;
    SPFLOAT in = 0, out = 0;
    sp_ftbl *ft;

    sp_conv *unit[NUM];

    sp_ftbl_loadfile(sp, &ft, SAMPDIR "oneart.wav");

    for(u = 0; u < NUM; u++) { 
        sp_conv_create(&unit[u]);
        sp_conv_init(sp, unit[u], ft, 2048);
    }

    for(t = 0; t < sp->len; t++) {
        for(u = 0; u < NUM; u++) sp_conv_compute(sp, unit[u], &in, &out);
    }

    for(u = 0; u < NUM; u++) sp_conv_destroy(&unit[u]);

    sp_ftbl_destroy(&ft);
    sp_destroy(&sp);
    return 0;
}

