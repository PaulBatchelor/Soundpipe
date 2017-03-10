#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "soundpipe.h"

typedef struct {
    sp_sparec *sparec;
    sp_osc *osc;
    sp_ftbl *ft; 
} UserData;

void process(sp_data *sp, void *udata) {
    UserData *ud = udata;
    SPFLOAT osc = 0, sparec = 0;
    sp_osc_compute(sp, ud->osc, NULL, &osc);
    sp_sparec_compute(sp, ud->sparec, &osc, &sparec);
    sp->out[0] = osc;
}

int main() {
    UserData ud;
    sp_data *sp;
    sp_create(&sp);
    sp_srand(sp, 1234567);

    sp_sparec_create(&ud.sparec);
    sp_osc_create(&ud.osc);
    sp_ftbl_create(sp, &ud.ft, 2048);

    sp_sparec_init(sp, ud.sparec, "rec.spa");
    sp_gen_sine(sp, ud.ft);
    sp_osc_init(sp, ud.osc, ud.ft, 0);

    sp->len = 44100 * 5;
    sp_process(sp, &ud, process);

    sp_sparec_close(sp, ud.sparec);
    sp_sparec_destroy(&ud.sparec);
    sp_ftbl_destroy(&ud.ft);
    sp_osc_destroy(&ud.osc);

    sp_destroy(&sp);
    return 0;
}
