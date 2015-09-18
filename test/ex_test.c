#include <stdlib.h>
#include <stdio.h>
#include "soundpipe.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    sp_osc *osc;
    sp_ftbl *ft;
} UserData;

typedef struct {
    sp_data *sp;
    uint32_t size;
} test_data;

int test_ex(sp_test *tst, test_data *td) 
{
    uint32_t n;
    int fail = 0;
    UserData ud;
    const char *hash = "31628d6589000de3b2cda9997ca15581";

    sp_osc_create(&ud.osc);
    sp_ftbl_create(td->sp, &ud.ft, 4096);
    sp_gen_sine(td->sp, ud.ft);
    sp_osc_init(td->sp, ud.osc, ud.ft, 0);
    
    for(n = 0; n < td->size; n++) {
        sp_osc_compute(td->sp, ud.osc, NULL, &td->sp->out[0]);
        sp_test_add_sample(tst, td->sp->out[0]);
    }
  

    if(sp_test_compare(tst, hash) == SP_NOT_OK) {
        printf("generated hash %s does not match reference hash %s\n", 
                tst->md5string, hash);
        fail = 1;
    }
     

    sp_osc_destroy(&ud.osc);
    sp_ftbl_destroy(&ud.ft);

    if(fail) return SP_NOT_OK;
    else return SP_OK;
}


typedef struct {
    int (* func)(sp_test *, test_data *);
    const char *desc;
} test_entry;

int main() 
{
    test_entry tests [] = {
        {test_ex, "test sine"}
    };

    plan(1);
    sp_test *tst;
    test_data td;
    sp_data *sp;
    sp_create(&sp);

    uint32_t size = 44100 * 5;

    td.sp = sp;
    td.size = size;

    sp_test_create(&tst, size);
    ok(tests[0].func(tst, &td)  == SP_OK, tests[0].desc);
    sp_test_destroy(&tst);

    sp_destroy(&sp);
    return 0;
}
