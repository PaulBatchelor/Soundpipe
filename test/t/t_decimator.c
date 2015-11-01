#include "soundpipe.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    sp_decimator *decimator;
    sp_noise *nz;
} UserData;

int t_decimator(sp_test *tst, sp_data *sp, const char *hash) 
{
    sp_srand(sp, 0); 
    uint32_t n;
    int fail = 0;
    SPFLOAT noise = 0, decimator = 0;
    UserData ud;

    sp_decimator_create(&ud.decimator);
    sp_noise_create(&ud.nz);

    sp_noise_init(sp, ud.nz);
    sp_decimator_init(sp, ud.decimator);
    ud.decimator->bitdepth = 8;
    ud.decimator->srate = 10000;

    for(n = 0; n < tst->size; n++) {
        noise = 0, decimator = 0;
        sp_noise_compute(sp, ud.nz, NULL, &noise);
        sp_decimator_compute(sp, ud.decimator, &noise, &decimator);
        sp_test_add_sample(tst, decimator);
    }
    
    fail = sp_test_verify(tst, hash);

    sp_decimator_destroy(&ud.decimator);
    sp_noise_destroy(&ud.nz);
     
    if(fail) return SP_NOT_OK;
    else return SP_OK;
}
