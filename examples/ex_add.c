#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "soundpipe.h"

typedef struct {
    sp_add *add;
    sp_osc *osc1;
    sp_osc *osc2;
    sp_ftbl *ft;
} UserData;

void process(sp_data *sp, void *udata) {
    UserData *ud = udata;
    SPFLOAT osc1 = 0, osc2 = 0, add = 0;
    sp_osc_compute(sp, ud->osc1, NULL, &osc1);
    sp_osc_compute(sp, ud->osc2, NULL, &osc2);
    sp_add_compute(sp, ud->add, &osc1, &osc2, &add);
    sp->out[0] = add;
}

int main() {
    srand(1234567);
    UserData ud;
    sp_data *sp;
    sp_create(&sp);

    sp_add_create(&ud.add);
    sp_osc_create(&ud.osc1);
    sp_osc_create(&ud.osc2);
    sp_ftbl_create(sp, &ud.ft, 2048);

    sp_add_init(sp, ud.add);
    sp_gen_sine(sp, ud.ft);
    sp_osc_init(sp, ud.osc1, ud.ft, 0);
    sp_osc_init(sp, ud.osc2, ud.ft, 0);

    ud.osc2->freq = 610;
    sp->len = 44100 * 5;
    sp_process(sp, &ud, process);

    sp_add_destroy(&ud.add);
    sp_ftbl_destroy(&ud.ft);
    sp_osc_destroy(&ud.osc1);
    sp_osc_destroy(&ud.osc2);

    sp_destroy(&sp);
    return 0;
}
