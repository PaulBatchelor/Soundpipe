#include "soundpipe.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

int t_gen_sinesum(sp_test *tst, sp_data *sp, const char *hash) 
{
    uint32_t n;
    int fail = 0;

    sp_ftbl *ft;
    sp_ftbl_create(sp, &ft, 4096);
    sp_gen_sinesum(sp, ft, "1 0.5 0.25");

    for(n = 0; n < ft->size; n++) {
        sp_test_add_sample(tst, ft->tbl[n]);
    }

    fail = sp_test_verify(tst, hash);

    sp_ftbl_destroy(&ft);

    if(fail) return SP_NOT_OK;
    else return SP_OK;
}
