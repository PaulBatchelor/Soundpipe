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
    sp_ftbl *wav;
    sp_ftbl *win;

    sp_fog *unit[NUM];
    
    sp_ftbl_loadfile(sp, &wav, SAMPDIR "oneart.wav");
    sp_ftbl_create(sp, &win, 1024);
    sp_gen_composite(sp, win, "0.5 0.5 270 0.5");

    for(u = 0; u < NUM; u++) { 
        sp_fog_create(&unit[u]);
        sp_fog_init(sp, unit[u], win, wav, 100, 0);
    }

    for(t = 0; t < sp->len; t++) {
        for(u = 0; u < NUM; u++) sp_fog_compute(sp, unit[u], &in, &out);
    }

    for(u = 0; u < NUM; u++) sp_fog_destroy(&unit[u]);

    sp_destroy(&sp);
    sp_ftbl_destroy(&wav);
    sp_ftbl_destroy(&win);
    return 0;
}

