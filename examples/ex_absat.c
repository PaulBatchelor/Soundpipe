#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "soundpipe.h"

typedef struct {
    sp_absat *absat;
    sp_osc *osc;
    sp_ftbl *ft;
} UserData;

void process(sp_data *sp, void *udata) {
    UserData *ud = udata;
    SPFLOAT osc = 0, absat;
    sp_osc_compute(sp, ud->osc, NULL, &osc);
    sp_absat_compute(sp, ud->absat, &osc, &absat);
    sp->out[0] = absat;
}

int main() {
    srand(1234567);
    UserData ud;
    sp_data *sp;
    sp_create(&sp);

    sp_absat_create(&ud.absat);
    sp_osc_create(&ud.osc);
    sp_ftbl_create(sp, &ud.ft, 2048);

    sp_absat_init(sp, ud.absat);
    sp_gen_sine(sp, ud.ft);
    sp_osc_init(sp, ud.osc, ud.ft, 0);
    ud.osc->amp = 0.5;
		ud.absat->dcOffset = 4;
		ud.absat->drive = 20;
    sp->len = 44100 * 5;
    sp_process(sp, &ud, process);

    sp_absat_destroy(&ud.absat);
    sp_ftbl_destroy(&ud.ft);
    sp_osc_destroy(&ud.osc);

    sp_destroy(&sp);
    return 0;
}
