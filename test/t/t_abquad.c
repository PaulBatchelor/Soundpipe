#include "soundpipe.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    sp_abquad *abquad;
    sp_osc *osc;
    sp_ftbl *ft;
} UserData;

int t_abquad(sp_test *tst, sp_data *sp, const char *hash)
{
    sp_srand(sp, 12345);
    uint32_t n;
    int fail = 0;
    UserData ud;
		SPFLOAT osc = 0, abquad = 0;

    sp_abquad_create(&ud.abquad);
    sp_osc_create(&ud.osc);
    sp_ftbl_create(sp, &ud.ft, 2048);

    sp_abquad_init(sp, ud.abquad);
    sp_gen_sine(sp, ud.ft);
    sp_osc_init(sp, ud.osc, ud.ft, 0);
    ud.osc->amp = 0.5;
		sp_abquad_set(sp, ud.abquad, 2.60687e-05, 2.98697e-05, 2.60687e-05, -1.31885, 0.437162);
    sp->len = 44100 * 5;

		for(n = 0; n < tst->size; n++) {
				sp_osc_compute(sp, ud.osc, NULL, &osc);
   			sp_abquad_compute(sp, ud.abquad, &osc, &abquad);
				sp_test_add_sample(tst, abquad);
		}

		fail = sp_test_verify(tst, hash);

		sp_abquad_destroy(&ud.abquad);
    sp_ftbl_destroy(&ud.ft);
    sp_osc_destroy(&ud.osc);

    if(fail) return SP_NOT_OK;
    else return SP_OK;
}
