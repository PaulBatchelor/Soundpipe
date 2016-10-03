#include <stdlib.h>
#include <stdio.h>
#include "soundpipe.h"
#include "config.h"

int main() {
    srand(time(NULL));
    sp_data *sp;
    sp_create(&sp);
    sp->sr = SR;
    sp->len = sp->sr * LEN;
    uint32_t t;
    SPFLOAT in = 0, out = 0;

    sp_moogladder *moog;
    sp_moogladder_create(&moog);

    sp_moogladder_init(sp, moog);

    for(t = 0; t < sp->len; t++) {
        sp_moogladder_compute(sp, moog, &in, &out);
    }

    sp_moogladder_destroy(&moog);
    sp_destroy(&sp);
    return 0;
}
