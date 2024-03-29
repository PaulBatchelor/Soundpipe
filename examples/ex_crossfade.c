#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "soundpipe.h"

typedef struct {
    sp_crossfade *crossfade;
    sp_osc *osc;
    sp_ftbl *ft;
    sp_osc *lfo;
    sp_noise *ns;
} UserData;

void process(sp_data *sp, void *udata) {
    UserData *ud = udata;
    SPFLOAT osc = 0, crossfade = 0, ns = 0, lfo = 0;
    sp_osc_compute(sp, ud->osc, NULL, &osc);
    sp_osc_compute(sp, ud->lfo, NULL, &lfo);
    sp_noise_compute(sp, ud->ns, NULL, &ns);
    ud->crossfade->pos = (lfo + 1) * 0.5;
    sp_crossfade_compute(sp, ud->crossfade, &osc, &ns, &crossfade);
    sp->out[0] = crossfade;
}

int main() {
    UserData ud;
    sp_data *sp;
    sp_create(&sp);

    sp_crossfade_create(&ud.crossfade);
    sp_osc_create(&ud.osc);
    sp_ftbl_create(sp, &ud.ft, 2048);
    sp_osc_create(&ud.lfo);
    sp_noise_create(&ud.ns);

    sp_crossfade_init(sp, ud.crossfade);
    sp_gen_sine(sp, ud.ft);
    sp_osc_init(sp, ud.osc, ud.ft, 0);
    sp_osc_init(sp, ud.lfo, ud.ft, 0);
    ud.lfo->amp = 1;
    ud.lfo->freq = 1;
    sp_noise_init(sp, ud.ns);
    ud.ns->amp = 0.1;


    sp->len = 44100 * 5;
    sp_process(sp, &ud, process);

    sp_crossfade_destroy(&ud.crossfade);
    sp_ftbl_destroy(&ud.ft);
    sp_osc_destroy(&ud.osc);
    sp_osc_destroy(&ud.lfo);
    sp_noise_destroy(&ud.ns);

    sp_destroy(&sp);
    return 0;
}
