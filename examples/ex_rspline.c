#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "soundpipe.h"

typedef struct {
    sp_rspline *rspline;
    sp_osc *osc;
    sp_ftbl *ft; 
} UserData;

void process(sp_data *sp, void *udata) {
    UserData *ud = udata;
    SPFLOAT osc = 0, rspline = 0;
    sp_rspline_compute(sp, ud->rspline, NULL, &rspline);
    ud->osc->freq = rspline;
    sp_osc_compute(sp, ud->osc, NULL, &osc);
    sp->out[0] = osc;
}

int main() {
    UserData ud;
    sp_data *sp;
    sp_create(&sp);
    sp_srand(sp, 1234567);

    sp_rspline_create(&ud.rspline);
    sp_osc_create(&ud.osc);
    sp_ftbl_create(sp, &ud.ft, 2048);

    sp_rspline_init(sp, ud.rspline);
    ud.rspline->min = 300;
    ud.rspline->max = 900;
    ud.rspline->cps_min = 0.1;
    ud.rspline->cps_max = 3;
    sp_gen_sine(sp, ud.ft);
    sp_osc_init(sp, ud.osc, ud.ft, 0);

    sp->len = 44100 * 5;
    sp_process(sp, &ud, process);

    sp_rspline_destroy(&ud.rspline);
    sp_ftbl_destroy(&ud.ft);
    sp_osc_destroy(&ud.osc);

    sp_destroy(&sp);
    return 0;
}
