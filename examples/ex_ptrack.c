#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "soundpipe.h"

typedef struct {
    sp_ptrack *ptrack;
    sp_osc *osc;
    sp_ftbl *ft;
    sp_osc *sig;
    sp_randh *randh;
} UserData;

void process(sp_data *sp, void *udata) {
    UserData *ud = udata;
    SPFLOAT freq = 0, amp = 0, sig = 0, randh = 0, osc = 0;
    sp_randh_compute(sp, ud->randh, NULL, &randh);
    ud->sig->freq = 800;
    //sp_blsaw_compute(sp, ud->sig, NULL, &sig);
    sp_osc_compute(sp, ud->sig, NULL, &sig);
    sp_ptrack_compute(sp, ud->ptrack, &sig, &freq, &amp);
    ud->osc->freq = freq;
    sp_osc_compute(sp, ud->osc, NULL, &osc);
    sp->out[0] = osc;
}

int main() {
    srand(1234567);
    UserData ud;
    sp_data *sp;
    sp_create(&sp);

    sp_ptrack_create(&ud.ptrack);
    sp_osc_create(&ud.osc);
    sp_ftbl_create(sp, &ud.ft, 2048);
   // sp_blsaw_create(&ud.sig);
    sp_osc_create(&ud.sig);
    sp_randh_create(&ud.randh);

    sp_ptrack_init(sp, ud.ptrack, 512, 20);
    sp_randh_init(sp, ud.randh);
    ud.randh->max = 500;
    ud.randh->min = 200;
    ud.randh->freq = 6;


    sp_gen_sine(sp, ud.ft);
    sp_osc_init(sp, ud.osc, ud.ft, 0);

    //sp_blsaw_init(sp, ud.sig);
    sp_osc_init(sp, ud.sig, ud.ft, 0);
    ud.sig->amp = 0.5;

    sp->len = 44100 * 5;
    sp_process(sp, &ud, process);

    sp_osc_destroy(&ud.sig);
    sp_randh_destroy(&ud.randh);
    sp_ptrack_destroy(&ud.ptrack);
    sp_ftbl_destroy(&ud.ft);
    sp_osc_destroy(&ud.osc);

    sp_destroy(&sp);
    return 0;
}
