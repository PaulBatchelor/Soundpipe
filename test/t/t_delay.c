#include "soundpipe.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    sp_delay *delay;
    sp_osc *osc;
    sp_metro *met;
    sp_tenv *tenv;
    sp_ftbl *ft;
} UserData;

int t_delay(sp_test *tst, sp_data *sp, const char *hash) 
{
    srand(1234567);
    uint32_t n;
    int fail = 0;
    SPFLOAT osc = 0, delay = 0, met = 0, tenv = 0;
    UserData ud;

    sp_delay_create(&ud.delay);
    sp_osc_create(&ud.osc);
    sp_ftbl_create(sp, &ud.ft, 2048);
    sp_metro_create(&ud.met);
    sp_tenv_create(&ud.tenv);

    sp_delay_init(sp, ud.delay, 0.75 * 0.5);
    ud.delay->feedback = 0.5;
    sp_gen_sine(sp, ud.ft);
    sp_osc_init(sp, ud.osc, ud.ft, 0);
    ud.osc->amp = 0.5;
    sp_metro_init(sp, ud.met);
    ud.met->freq = 1;
    sp_tenv_init(sp, ud.tenv);
    ud.tenv->atk = 0.005;
    ud.tenv->hold = 0.1;
    ud.tenv->rel =  0.1;



    for(n = 0; n < tst->size; n++) {
        osc = 0, delay = 0, met = 0, tenv = 0;
        sp_metro_compute(sp, ud.met, NULL, &met);
        sp_tenv_compute(sp, ud.tenv, &met, &tenv);
        if(met) {
            ud.osc->freq = 100 + rand() % 500;
        }
        sp_osc_compute(sp, ud.osc, NULL, &osc);
        osc *= tenv;
        sp_delay_compute(sp, ud.delay, &osc, &delay);

        sp_test_add_sample(tst, osc + delay);
    }

    if(sp_test_compare(tst, hash) == SP_NOT_OK) {
        printf("Generated hash %s does not match reference hash %s\n", 
                tst->md5string, hash);
        fail = 1;
    }
     
    if(fail) return SP_NOT_OK;
    else return SP_OK;
}
