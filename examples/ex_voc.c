
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "soundpipe.h"

typedef struct {
    sp_voc *voc;
    sp_osc *osc;
    sp_ftbl *ft;
} UserData;

void process(sp_data *sp, void *udata) {
    UserData *ud = udata;
    SPFLOAT osc = 0, voc = 0;
    sp_osc_compute(sp, ud->osc, NULL, &osc);
    if(sp_voc_get_counter(ud->voc) == 0) {
        osc = 12 + 16 * (0.5 * (osc + 1));
        sp_voc_set_tongue_shape(ud->voc, osc, 2.9);
    }
    sp_voc_compute(sp, ud->voc, &voc);
    sp->out[0] = voc;
}

int main() {
    UserData ud;
    sp_data *sp;
    sp_create(&sp);
    sp_srand(sp, 1234567);

    sp_voc_create(&ud.voc);
    sp_osc_create(&ud.osc);
    sp_ftbl_create(sp, &ud.ft, 2048);

    sp_voc_init(sp, ud.voc);
    sp_gen_sine(sp, ud.ft);
    sp_osc_init(sp, ud.osc, ud.ft, 0);
    ud.osc->amp = 1;
    ud.osc->freq = 0.1;

    sp->len = 44100 * 5;
    sp_process(sp, &ud, process);

    sp_voc_destroy(&ud.voc);
    sp_ftbl_destroy(&ud.ft);
    sp_osc_destroy(&ud.osc);

    sp_destroy(&sp);
    return 0;
}

