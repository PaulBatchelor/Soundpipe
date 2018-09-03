#include "soundpipe.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    sp_osc *osc;
    sp_ftbl *ft;
    sp_metro *met;
    sp_tenvx *tenvx;
    SPFLOAT freq;
} UserData;

int t_tenvx(sp_test *tst, sp_data *sp, const char *hash)
{
    uint32_t n;
    int fail = 0;

    UserData ud;
    SPFLOAT *freqp = &ud.freq;
    ud.freq = 400;
    sp_srand(sp, 123456);

    sp_tenvx_create(&ud.tenvx);
    sp_metro_create(&ud.met);
    sp_ftbl_create(sp, &ud.ft, 2048);
    sp_osc_create(&ud.osc);

    sp_tenvx_init(sp, ud.tenvx);
    ud.tenvx->atk = 0.03;
    ud.tenvx->hold = 0.1;
    ud.tenvx->rel = 0.1;
    sp_metro_init(sp, ud.met);
    ud.met->freq = 3;
    sp_gen_sine(sp, ud.ft);
    sp_osc_init(sp, ud.osc, ud.ft, 0);
    ud.osc->amp = 0.5;
    ud.osc->freq = *freqp;

    for(n = 0; n < tst->size; n++) {
        SPFLOAT trig = 0;
        SPFLOAT env = 0;
        SPFLOAT osc = 0;
        sp_metro_compute(sp, ud.met, NULL, &trig);
        if(trig) ud.osc->freq = 500 + sp_rand(sp) % 2000;
        sp_osc_compute(sp, ud.osc, NULL, &osc);
        sp_tenvx_compute(sp, ud.tenvx, &trig, &env);
        sp_test_add_sample(tst, osc * env);
    }

    fail = sp_test_verify(tst, hash);

    sp_tenvx_destroy(&ud.tenvx);
    sp_metro_destroy(&ud.met);
    sp_ftbl_destroy(&ud.ft);
    sp_osc_destroy(&ud.osc);

    if(fail) return SP_NOT_OK;
    else return SP_OK;
}
