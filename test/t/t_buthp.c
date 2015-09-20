#include "soundpipe.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    sp_noise *ns;
    sp_buthp *buthp;
} udata;

int t_buthp(sp_test *tst, sp_data *sp, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    SPFLOAT in = 0;
    SPFLOAT out = 0;
    
    udata ud;
    sp_noise_create(&ud.ns);
    sp_buthp_create(&ud.buthp);
    sp_noise_init(sp, ud.ns);
    sp_buthp_init(sp, ud.buthp);
    ud.buthp->freq = 5000;

    for(n = 0; n < tst->size; n++) {
        in = 0;
        out = 0;
        sp_noise_compute(sp, ud.ns, NULL, &in);
        sp_buthp_compute(sp, ud.buthp, &in, &out); 
        sp_test_add_sample(tst, out);
    }

    if(sp_test_compare(tst, hash) == SP_NOT_OK) {
        printf("Generated hash %s does not match reference hash %s\n", 
                tst->md5string, hash);
        fail = 1;
    }
    
    sp_noise_destroy(&ud.ns);
    sp_buthp_destroy(&ud.buthp);
     
    if(fail) return SP_NOT_OK;
    else return SP_OK;
}
