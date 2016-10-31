#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "soundpipe.h"


static const SPFLOAT coefs[] =
	{2.60687e-05, 2.98697e-05, 2.60687e-05, -1.31885, 0.437162};

typedef struct {
    sp_abquad *abquad;
    sp_osc *osc;
    sp_ftbl *ft;
} UserData;

void process(sp_data *sp, void *udata) {
    UserData *ud = udata;
    SPFLOAT osc = 0, abquad = 0;
    sp_osc_compute(sp, ud->osc, NULL, &osc);
    sp_abquad_compute(sp, ud->abquad, &osc, &absat);
    sp->out[0] = abquad;
}

int main() {
    srand(1234567);
    UserData ud;
    sp_data *sp;
    sp_create(&sp);

    sp_abquad_create(&ud.abquad);
    sp_osc_create(&ud.osc);
    sp_ftbl_create(sp, &ud.ft, 2048);
    sp_abquad_init(sp, ud.abquad);
    sp_gen_sine(sp, ud.ft);
    sp_osc_init(sp, ud.osc, ud.ft, 0);
		sp_abquad_set(sp, ud.abquad, coefs);
    ud.osc->amp = 0.5;
    sp->len = 44100 * 5;
    sp_process(sp, &ud, process);

    sp_abquad_destroy(&ud.abquad);
    sp_ftbl_destroy(&ud.ft);
    sp_osc_destroy(&ud.osc);

    sp_destroy(&sp);
    return 0;
}
