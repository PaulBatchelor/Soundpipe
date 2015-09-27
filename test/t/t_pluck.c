#include "soundpipe.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    sp_pluck *pluck;
    sp_osc *osc;
    sp_ftbl *ft;
    sp_metro *met;
} udata;

int t_pluck(sp_test *tst, sp_data *sp, const char *hash) 
{
    uint32_t n;
    int fail = 0;

    /* allocate / initialize modules here */
    udata ud;
    sp_srand(sp, 0); 

    sp_pluck_create(&ud.pluck);
    sp_osc_create(&ud.osc);
    sp_metro_create(&ud.met);
    sp_ftbl_create(sp, &ud.ft, 2048);

    sp_pluck_init(sp, ud.pluck, 110);
    sp_gen_sine(sp, ud.ft);
    sp_metro_init(sp, ud.met);
    ud.met->freq = 2;
    sp_osc_init(sp, ud.osc, ud.ft, 0);

    ud.osc->freq = 1;
    ud.osc->amp = 1;

    for(n = 0; n < tst->size; n++) {
        /* compute samples and add to test buffer */
        SPFLOAT osc = 0, pluck = 0, met = 0;
        sp_osc_compute(sp, ud.osc, NULL, &osc);
        sp_metro_compute(sp, ud.met, NULL, &met);
        if(met) {
            ud.pluck->reflect = 0.5;
            ud.pluck->freq = ud.pluck->ifreq + sp_rand(sp) % 500;
        }
        sp_pluck_compute(sp, ud.pluck, &met, &osc, &pluck);
        sp->out[0] = pluck;
        sp_test_add_sample(tst, sp->out[0]);
    }

    if(sp_test_compare(tst, hash) == SP_NOT_OK) {
        printf("Generated hash %s does not match reference hash %s\n", 
                tst->md5string, hash);
        fail = 1;
    }
    
    /* destroy functions here */
    sp_pluck_destroy(&ud.pluck);
    sp_ftbl_destroy(&ud.ft);
    sp_osc_destroy(&ud.osc);
    sp_metro_destroy(&ud.met);

    if(fail) return SP_NOT_OK;
    else return SP_OK;
}
