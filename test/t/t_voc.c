
#include "soundpipe.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    sp_voc *voc;
    sp_osc *osc;
    sp_ftbl *ft;
} UserData;

int t_voc(sp_test *tst, sp_data *sp, const char *hash)
{
    uint32_t n;
    UserData ud;

    int fail = 0;
    SPFLOAT osc, voc;
    sp_voc_create(&ud.voc);
    sp_osc_create(&ud.osc);
    sp_ftbl_create(sp, &ud.ft, 2048);

    sp_voc_init(sp, ud.voc);
    sp_gen_sine(sp, ud.ft);
    sp_osc_init(sp, ud.osc, ud.ft, 0);
    ud.osc->amp = 1;
    ud.osc->freq = 0.1;

    for(n = 0; n < tst->size; n++) {
        /* compute samples and add to test buffer */
        osc = 0;
        voc = 0;
        sp_osc_compute(sp, ud.osc, NULL, &osc);
        if(sp_voc_get_counter(ud.voc) == 0) {
            osc = 12 + 16 * (0.5 * (osc + 1));
            sp_voc_set_tongue_shape(ud.voc, osc, 2.9);
        }
        sp_voc_compute(sp, ud.voc, &voc);
        sp_test_add_sample(tst, voc);
    }

    fail = sp_test_verify(tst, hash);

    sp_voc_destroy(&ud.voc);
    sp_ftbl_destroy(&ud.ft);
    sp_osc_destroy(&ud.osc);

    if(fail) return SP_NOT_OK;
    else return SP_OK;
}

