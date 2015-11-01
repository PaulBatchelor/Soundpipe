#include "soundpipe.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    sp_div *div;
    sp_osc *osc1;
    sp_osc *osc2;
    sp_ftbl *ft;
} UserData;

int t_div(sp_test *tst, sp_data *sp, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    UserData ud;
    
    sp_div_create(&ud.div);
    sp_osc_create(&ud.osc1);
    sp_osc_create(&ud.osc2);
    sp_ftbl_create(sp, &ud.ft, 2048);

    sp_div_init(sp, ud.div);
    sp_gen_sine(sp, ud.ft);
    sp_osc_init(sp, ud.osc1, ud.ft, 0);
    sp_osc_init(sp, ud.osc2, ud.ft, 0);

    ud.osc2->freq = 610;

    for(n = 0; n < tst->size; n++) {
        SPFLOAT osc1 = 0, osc2 = 0, div = 0;
        sp_osc_compute(sp, ud.osc1, NULL, &osc1);
        osc1 += 2;
        sp_osc_compute(sp, ud.osc2, NULL, &osc2);
        sp_div_compute(sp, ud.div, &osc1, &osc2, &div);
        sp_test_add_sample(tst, div);
    }

    fail = sp_test_verify(tst, hash);
    
    sp_div_destroy(&ud.div);
    sp_ftbl_destroy(&ud.ft);
    sp_osc_destroy(&ud.osc1);
    sp_osc_destroy(&ud.osc2);
     
    if(fail) return SP_NOT_OK;
    else return SP_OK;
}
