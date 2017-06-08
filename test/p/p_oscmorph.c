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

    sp_ftbl *ft[2];
    sp_ftbl *ft1;
    sp_ftbl *ft2;

    sp_oscmorph *unit[NUM];

    sp_ftbl_create(sp, &ft1, 4096);
    sp_gen_sine(sp, ft1);
    sp_ftbl_create(sp, &ft2, 4096);
    sp_gen_sinesum(sp, ft2, "1 1 1");

    ft[0] = ft1;
    ft[1] = ft2;

    for(u = 0; u < NUM; u++) { 
        sp_oscmorph_create(&unit[u]);
        sp_oscmorph_init(sp, unit[u], ft, 2, 0);
    }

    for(t = 0; t < sp->len; t++) {
        for(u = 0; u < NUM; u++) sp_oscmorph_compute(sp, unit[u], &in, &out);
    }

    for(u = 0; u < NUM; u++) sp_oscmorph_destroy(&unit[u]);

    sp_ftbl_destroy(&ft1);
    sp_ftbl_destroy(&ft2);
    sp_destroy(&sp);
    return 0;
}

