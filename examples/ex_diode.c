#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "soundpipe.h"

typedef struct {
    sp_diode *diode;
    sp_noise *ns;
    sp_osc *lfo;
    sp_ftbl *ft;
} UserData;

void process(sp_data *sp, void *udata) {
    UserData *ud = udata;
    SPFLOAT ns = 0;
    SPFLOAT diode = 0;
    SPFLOAT lfo = 0;
    sp_osc_compute(sp, ud->lfo, NULL, &lfo);
    sp_noise_compute(sp, ud->ns, NULL, &ns);
    ud->diode->freq = 2000 + lfo * 1800;
    sp_diode_compute(sp, ud->diode, &ns, &diode);
    sp_out(sp, 0, diode);
}

int main() {
    UserData ud;
    sp_data *sp;
    sp_create(&sp);
    sp_srand(sp, 1234567);

    sp_diode_create(&ud.diode);
    sp_noise_create(&ud.ns);
    sp_osc_create(&ud.lfo);
    sp_ftbl_create(sp, &ud.ft, 8192);
    sp_gen_sine(sp, ud.ft);

    sp_diode_init(sp, ud.diode);
    sp_noise_init(sp, ud.ns);
    sp_osc_init(sp, ud.lfo, ud.ft, 0);
    ud.lfo->freq = 0.5;
    ud.lfo->amp = 1.0;
    ud.diode->res = 0.9;

    sp->len = 44100 * 5;
    sp_process(sp, &ud, process);

    sp_diode_destroy(&ud.diode);
    sp_noise_destroy(&ud.ns);
    sp_osc_destroy(&ud.lfo);

    sp_destroy(&sp);
    return 0;
}
