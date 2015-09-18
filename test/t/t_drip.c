#include "soundpipe.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    sp_drip *drip;
    sp_dust *trig;
    sp_revsc *rev;
} udata;

int t_drip(sp_test *tst, sp_data *sp, const char *hash) 
{
    srand(1234567);
    uint32_t n;
    int fail = 0;
    SPFLOAT trig, rev1, rev2, drip;
    udata ud;

    sp_revsc_create(&ud.rev);
    sp_drip_create(&ud.drip);
    sp_dust_create(&ud.trig);
    
    sp_dust_init(sp, ud.trig, 1, 1);
    sp_drip_init(sp, ud.drip, 0.09);
    ud.drip->amp = 0.3;
    sp_revsc_init(sp, ud.rev);
    ud.rev->feedback = 0.9;
    
    for(n = 0; n < tst->size; n++) {
        sp_dust_compute(sp, ud.trig, NULL, &trig);
        sp_drip_compute(sp, ud.drip, &trig, &drip);
        sp_revsc_compute(sp, ud.rev, &drip, &drip, &rev1, &rev2);
        sp_test_add_sample(tst, drip + rev1 * 0.05);
    }

    if(sp_test_compare(tst, hash) == SP_NOT_OK) {
        printf("Generated hash %s does not match reference hash %s\n", 
                tst->md5string, hash);
        fail = 1;
    }
    
    sp_drip_destroy(&ud.drip);
    sp_dust_destroy(&ud.trig);
    sp_revsc_destroy(&ud.rev);
     
    if(fail) return SP_NOT_OK;
    else return SP_OK;
}
