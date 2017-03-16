#include "soundpipe.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    sp_rspline *rspline;
    sp_osc *osc;
    sp_ftbl *ft; 
} UserData;

int t_rspline(sp_test *tst, sp_data *sp, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    SPFLOAT osc, rspline;

    UserData ud;
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

    for(n = 0; n < tst->size; n++) {
        /* compute samples and add to test buffer */
        osc = 0; 
        rspline = 0;
        sp_rspline_compute(sp, ud.rspline, NULL, &rspline);
        ud.osc->freq = rspline;
        sp_osc_compute(sp, ud.osc, NULL, &osc);
        sp_test_add_sample(tst, osc);
    }

    fail = sp_test_verify(tst, hash);
    
    sp_rspline_destroy(&ud.rspline);
    sp_ftbl_destroy(&ud.ft);
    sp_osc_destroy(&ud.osc);

    if(fail) return SP_NOT_OK;
    else return SP_OK;
}
