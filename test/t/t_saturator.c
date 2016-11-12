#include "soundpipe.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    sp_saturator *saturator;
    sp_osc *osc;
    sp_ftbl *ft;
} UserData;

int t_saturator(sp_test *tst, sp_data *sp, const char *hash)
{
    sp_srand(sp, 12345);
    uint32_t n;
    int fail = 0;
    UserData ud;
        SPFLOAT osc = 0, saturator = 0;

    sp_saturator_create(&ud.saturator);
    sp_osc_create(&ud.osc);
    sp_ftbl_create(sp, &ud.ft, 2048);

    sp_saturator_init(sp, ud.saturator);
    sp_gen_sine(sp, ud.ft);
    sp_osc_init(sp, ud.osc, ud.ft, 0);
    ud.osc->amp = 0.5;
    ud.saturator->dcoffset = 4;
    ud.saturator->drive = 20;
    sp->len = 44100 * 5;

    for(n = 0; n < tst->size; n++) {
        sp_osc_compute(sp, ud.osc, NULL, &osc);
        sp_saturator_compute(sp, ud.saturator, &osc, &saturator);
        sp_test_add_sample(tst, saturator);
    }

    fail = sp_test_verify(tst, hash);

    sp_saturator_destroy(&ud.saturator);
    sp_ftbl_destroy(&ud.ft);
    sp_osc_destroy(&ud.osc);

    if(fail) return SP_NOT_OK;
    else return SP_OK;
}
