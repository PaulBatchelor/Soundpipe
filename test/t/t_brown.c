#include "soundpipe.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    sp_brown *brown;
} UserData;

int t_brown(sp_test *tst, sp_data *sp, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    SPFLOAT brown = 0;

    UserData ud;
    sp_brown_create(&ud.brown);

    sp_brown_init(sp, ud.brown);

    for(n = 0; n < tst->size; n++) {
        sp_brown_compute(sp, ud.brown, NULL, &brown);
        sp_test_add_sample(tst, brown);
    }

    fail = sp_test_verify(tst, hash);
    
    sp_brown_destroy(&ud.brown);

    if(fail) return SP_NOT_OK;
    else return SP_OK;
}
