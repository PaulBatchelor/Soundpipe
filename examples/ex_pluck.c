#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "soundpipe.h"

typedef struct {
    sp_pluck *pluck;
    sp_osc *osc;
    sp_ftbl *ft; 
    sp_metro *met;
} UserData;

void process(sp_data *sp, void *udata) {
    UserData *ud = udata;
    SPFLOAT osc = 0, pluck = 0, met = 0;
    sp_osc_compute(sp, ud->osc, NULL, &osc);
    sp_metro_compute(sp, ud->met, NULL, &met);
    if(met) {
        ud->pluck->reflect = 0.5;
        ud->pluck->freq = ud->pluck->ifreq + rand() % 500;
    }
    sp_pluck_compute(sp, ud->pluck, &met, &osc, &pluck);
    sp->out[0] = pluck;
}

int main() {
    srand(1234567);
    UserData ud;
    sp_data *sp;
    sp_create(&sp);

    sp_pluck_create(&ud.pluck);
    sp_osc_create(&ud.osc);
    sp_metro_create(&ud.met);
    sp_ftbl_create(sp, &ud.ft, 2048);

    sp_pluck_init(sp, ud.pluck, 110);
    sp_gen_sine(sp, ud.ft);
    sp_metro_init(sp, ud.met, 2);
    sp_osc_init(sp, ud.osc, ud.ft, 0);

    ud.osc->freq = 1;
    ud.osc->amp = 1;

    sp->len = 44100 * 5;
    sp_process(sp, &ud, process);

    sp_pluck_destroy(&ud.pluck);
    sp_ftbl_destroy(&ud.ft);
    sp_osc_destroy(&ud.osc);
    sp_metro_destroy(&ud.met);

    sp_destroy(&sp);
    return 0;
}
