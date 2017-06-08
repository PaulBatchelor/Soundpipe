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

    sp_mincer *unit[NUM];
    sp_ftbl *wav;

    sp_ftbl_loadfile(sp, &wav, SAMPDIR "oneart.wav");

    for(u = 0; u < NUM; u++) { 
        sp_mincer_create(&unit[u]);
        sp_mincer_init(sp, unit[u], wav, 2048);
    }

    for(t = 0; t < sp->len; t++) {
        for(u = 0; u < NUM; u++) sp_mincer_compute(sp, unit[u], &in, &out);
    }

    for(u = 0; u < NUM; u++) sp_mincer_destroy(&unit[u]);

    sp_destroy(&sp);
    sp_ftbl_destroy(&wav);
    return 0;
}

