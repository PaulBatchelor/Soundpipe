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

    sp_lpf18 *unit;
    sp_lpf18_create(&unit);

    sp_lpf18_init(sp, unit);

    for(t = 0; t < sp->len; t++) {
        sp_lpf18_compute(sp, unit, &in, &out);
    }

    sp_lpf18_destroy(&unit);

    sp_destroy(&sp);
    return 0;
}

