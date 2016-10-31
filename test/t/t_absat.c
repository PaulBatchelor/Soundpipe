#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "soundpipe.h"

typedef struct {
    sp_absat *absat;
    sp_osc *osc;
    sp_ftbl *ft;
} UserData;

int t_absat(sp_test *tst, sp_data *sp, const char *hash)
{
    sp_srand(sp, 12345);
    uint32_t n;
    int fail = 0;
    srand(1234567);
    UserData ud;
		SPFLOAT osc = 0, absat = 0;

    sp_absat_create(&ud.absat);
    sp_osc_create(&ud.osc);
    sp_ftbl_create(sp, &ud.ft, 2048);

    sp_absat_init(sp, ud.absat);
    sp_gen_sine(sp, ud.ft);
    sp_osc_init(sp, ud.osc, ud.ft, 0);
    ud.osc->amp = 0.5;
		ud.absat->dcOffset = 4;
		ud.absat->drive = 20;
    sp->len = 44100 * 5;
    sp_process(sp, &ud, process);

		for(n = 0; n < tst->size; n++) {
				sp_osc_compute(sp, ud->osc, NULL, &osc);
   			sp_absat_compute(sp, ud->absat, &osc, &absat);
				sp_test_add_sample(tst, absat);
		}

		fail = sp_test_verify(tst, hash);

		sp_absat_destroy(&ud.absat);
    sp_ftbl_destroy(&ud.ft);
    sp_osc_destroy(&ud.osc);

    if(fail) return SP_NOT_OK;
    else return SP_OK;
}
