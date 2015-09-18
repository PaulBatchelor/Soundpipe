#include "soundpipe.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

int t_ex(sp_test *tst, sp_data *sp, const char *hash) 
{
    uint32_t n;
    int fail = 0;

    sp_osc *osc;
    sp_ftbl *ft;

    sp_osc_create(&osc);
    sp_ftbl_create(sp, &ft, 4096);
    sp_gen_sine(sp, ft);
    sp_osc_init(sp, osc, ft, 0);
    
    for(n = 0; n < tst->size; n++) {
        sp_osc_compute(sp, osc, NULL, &sp->out[0]);
        sp_test_add_sample(tst, sp->out[0]);
    }

    if(sp_test_compare(tst, hash) == SP_NOT_OK) {
        printf("Generated hash %s does not match reference hash %s\n", 
                tst->md5string, hash);
        fail = 1;
    }
     
    sp_osc_destroy(&osc);
    sp_ftbl_destroy(&ft);

    if(fail) return SP_NOT_OK;
    else return SP_OK;
}
