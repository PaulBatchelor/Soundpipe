#include "soundpipe.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct{
    sp_osc *osc;
    sp_ftbl *ft;
    sp_metro *mt;
    sp_tenv *te;
    sp_rpt *rpt;
    sp_maygate *mg;
} UserData;

int t_rpt(sp_test *tst, sp_data *sp, const char *hash)
{
    uint32_t n;
    int fail = 0;

    UserData ud;
    int tempo = 120;
    SPFLOAT met, osc, env, rpt, maygate, trig, dry;

    sp_rpt_create(&ud.rpt);
    sp_maygate_create(&ud.mg);
    sp_osc_create(&ud.osc);
    sp_ftbl_create(sp, &ud.ft, 4096);
    sp_metro_create(&ud.mt);
    sp_tenv_create(&ud.te);


    sp_maygate_init(sp, ud.mg);
    ud.mg->prob = 0.5;
    sp_gen_sine(sp, ud.ft);
    sp_osc_init(sp, ud.osc, ud.ft, 0);
    sp_metro_init(sp, ud.mt);
    ud.mt->freq = tempo / 60.0;
    sp_rpt_init(sp, ud.rpt, 1.0);
    ud.rpt->bpm = tempo;
    ud.rpt->div = 8;
    ud.rpt->rep = 4;
    sp_tenv_init(sp, ud.te);
    ud.te->atk = 0.001;
    ud.te->hold = 0.1;
    ud.te->rel =  0.1;


    /* allocate / initialize modules here */

    for(n = 0; n < tst->size; n++) {
        sp_metro_compute(sp, ud.mt, NULL, &met);
        sp_tenv_compute(sp, ud.te, &met, &env);
        sp_osc_compute(sp, ud.osc, NULL, &osc);
        dry = osc * env;
        sp_maygate_compute(sp, ud.mg, &met, &maygate);
        trig = met * maygate;
        sp_rpt_compute(sp, ud.rpt, &trig, &dry, &rpt);
        sp_test_add_sample(tst, rpt);
    }

    fail = sp_test_verify(tst, hash);

    /* destroy functions here */

    sp_maygate_destroy(&ud.mg);
    sp_tenv_destroy(&ud.te);
    sp_metro_destroy(&ud.mt);
    sp_ftbl_destroy(&ud.ft);
    sp_osc_destroy(&ud.osc);
    sp_rpt_destroy(&ud.rpt);

    if(fail) return SP_NOT_OK;
    else return SP_OK;
}
