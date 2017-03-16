#include "soundpipe.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    sp_spa *spa;
} UserData;

int t_spa(sp_test *tst, sp_data *sp, const char *hash) 
{
    UserData ud;
    uint32_t n;
    SPFLOAT spa;
    int fail = 0;

    sp_srand(sp, 1234567);
    sp_spa_create(&ud.spa);
    sp_spa_init(sp, ud.spa, SAMPDIR "oneart.spa");


    for(n = 0; n < tst->size; n++) {
        spa = 0;
        sp_spa_compute(sp, ud.spa, NULL, &spa);
        sp_test_add_sample(tst, spa);
    }

    fail = sp_test_verify(tst, hash);

    sp_spa_destroy(&ud.spa);

    if(fail) return SP_NOT_OK;
    else return SP_OK;
}
