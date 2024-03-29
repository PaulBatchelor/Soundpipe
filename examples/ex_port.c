#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "soundpipe.h"

typedef struct {
    sp_osc *osc;
    sp_metro *mt;
    sp_ftbl *sine, *nn;
    sp_tseq *seq;
    sp_port *prt;
} UserData;

void process(sp_data *sp, void *userdata) {
    UserData *ud = userdata;
    SPFLOAT osc, mt, nn, freq, pfreq;
    sp_metro_compute(sp, ud->mt, NULL, &mt);
    sp_tseq_compute(sp, ud->seq, &mt, &nn);
    freq = sp_midi2cps(nn);
    sp_port_compute(sp, ud->prt, &freq, &pfreq);
    ud->osc->freq = pfreq;
    sp_osc_compute(sp, ud->osc, NULL, &osc);
    sp->out[0] = osc;
}

int main() {
    srand(time(NULL));
    UserData ud;
    sp_data *sp;
    sp_create(&sp);

    sp_metro_create(&ud.mt);
    sp_ftbl_create(sp, &ud.sine, 2048);
    sp_ftbl_create(sp, &ud.nn, 1);
    sp_osc_create(&ud.osc);
    sp_port_create(&ud.prt);

    sp_gen_vals(sp, ud.nn, "60 63 65 60 63 67");
    sp_tseq_create(&ud.seq);
    sp_tseq_init(sp, ud.seq, ud.nn);

    sp_port_init(sp, ud.prt);
    ud.prt->smooth = 0.02;
    sp_metro_init(sp, ud.mt);
    ud.mt->freq = 4.0;
    sp_gen_sine(sp, ud.sine);
    sp_osc_init(sp, ud.osc, ud.sine, 0);
    sp->len = 44100 * 5;

    sp_process(sp, &ud, process);

    sp_port_destroy(&ud.prt);
    sp_tseq_destroy(&ud.seq);
    sp_metro_destroy(&ud.mt);
    sp_ftbl_destroy(&ud.sine);
    sp_ftbl_destroy(&ud.nn);
    sp_osc_destroy(&ud.osc);

    sp_destroy(&sp);
    return 0;
}
