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

    sp_butlp *unit;
    sp_butlp_create(&unit);

    sp_butlp_init(sp, unit);

    for(t = 0; t < sp->len; t++) {
        sp_butlp_compute(sp, unit, &in, &out);
    }

    sp_butlp_destroy(&unit);

    sp_destroy(&sp);
    return 0;
}

