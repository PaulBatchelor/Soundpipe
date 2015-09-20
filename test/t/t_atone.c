#include "soundpipe.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

int t_atone(sp_test *tst, sp_data *sp, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    SPFLOAT noise = 0, atone = 0;
    
    sp_atone *atone_d;
    sp_noise *noise_d;

    sp_atone_create(&atone_d);
    sp_noise_create(&noise_d);

    sp_atone_init(sp, atone_d);
    sp_noise_init(sp, noise_d);

    for(n = 0; n < tst->size; n++) {
        noise = 0, atone = 0;
        sp_noise_compute(sp, noise_d, NULL, &noise);
        sp_atone_compute(sp, atone_d, &noise, &atone);
        sp_test_add_sample(tst, atone);
    }

    if(sp_test_compare(tst, hash) == SP_NOT_OK) {
        printf("Generated hash %s does not match reference hash %s\n", 
                tst->md5string, hash);
        fail = 1;
    }
    
    sp_atone_destroy(&atone_d);
    sp_noise_destroy(&noise_d);
     
    if(fail) return SP_NOT_OK;
    else return SP_OK;
}
