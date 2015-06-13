#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "soundpipe.h"

typedef struct {
    sp_osc *osc;
    sp_ftbl *ft; 
} udata;

void write_osc(sp_data *data, void *ud) {
    udata *udp = ud;
    sp_osc_compute(data, udp->osc, NULL, &data->out);
}

int main() {
    srand(time(NULL));
    udata ud;
    sp_data *sp;
    sp_create(&sp);
    sp_ftbl_create(sp, &ud.ft, 4096);
    sp_osc_create(&ud.osc);

    sp_gen_sinesum(sp, ud.ft, "1 0 0 1");
    sp_osc_init(sp, ud.osc, ud.ft);
    ud.osc->freq = 500;
    sp->len = 44100 * 5;
    sp_process(sp, &ud, write_osc);

    sp_ftbl_destroy(&ud.ft);
    sp_osc_destroy(&ud.osc);
    sp_destroy(&sp);
    return 0;
}
