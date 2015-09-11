#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "soundpipe.h"

typedef struct {
    sp_abs *abs;
    sp_osc *osc;
    sp_ftbl *ft;
} UserData;

void process(sp_data *sp, void *udata) {
    UserData *ud = udata;
    SPFLOAT osc = 0, abs = 0;
    sp_osc_compute(sp, ud->osc, NULL, &osc);
    ud->osc->amp = 1;
    sp_abs_compute(sp, ud->abs, &osc, &abs);
    sp->out[0] = abs;
}

int main() {
    srand(1234567);
    UserData ud;
    sp_data *sp;
    sp_create(&sp);

    sp_abs_create(&ud.abs);
    sp_osc_create(&ud.osc);
    sp_ftbl_create(sp, &ud.ft, 2048);

    sp_abs_init(sp, ud.abs);
    sp_gen_sine(sp, ud.ft);
    sp_osc_init(sp, ud.osc, ud.ft, 0);

    sp->len = 44100 * 5;
    sp_process(sp, &ud, process);

    sp_abs_destroy(&ud.abs);
    sp_ftbl_destroy(&ud.ft);
    sp_osc_destroy(&ud.osc);

    sp_destroy(&sp);
    return 0;
}
