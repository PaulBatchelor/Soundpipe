#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "soundpipe.h"

typedef struct {
    sp_dust *dst;
} udata;

void write_dust(sp_data *data, void *ud) {
    udata *udata = ud;
    SPFLOAT in = 0;
    sp_dust_compute(data, udata->dst, NULL, &data->out[0]);
}
int main() {
    srand(time(NULL));
    udata ud;
    sp_data *sp;
    sp_create(&sp);
    sp_dust_create(&ud.dst);
    sp_dust_init(sp, ud.dst, 0.3, 10);
    sp->len = 44100 * 5;
    ud.dst->bipolar = 1.0;
    sp_process(sp, &ud, write_dust);
    sp_dust_destroy(&ud.dst);
    sp_destroy(&sp);
    return 0;
}
