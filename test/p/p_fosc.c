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
    sp_fosc *unit[NUM];
    sp_ftbl_create(sp, &ft, 8192);
    sp_gen_sine(sp, ft);

    for(u = 0; u < NUM; u++) { 
        sp_fosc_create(&unit[u]);
        sp_fosc_init(sp, unit[u], ft);
    }

    for(t = 0; t < sp->len; t++) {
        for(u = 0; u < NUM; u++) sp_fosc_compute(sp, unit[u], &in, &out);
    }

    for(u = 0; u < NUM; u++) sp_fosc_destroy(&unit[u]);

    sp_ftbl_destroy(&ft);
    sp_destroy(&sp);
    return 0;
}

