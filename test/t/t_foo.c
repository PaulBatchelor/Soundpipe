#include "soundpipe.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

int t_foo(sp_test *tst, sp_data *sp, const char *hash) 
{
    uint32_t n;
    int fail = 0;

    /* allocate / initialize modules here */

    for(n = 0; n < tst->size; n++) {
        /* compute samples and add to test buffer */
        sp_test_add_sample(tst, 0);
    }

    if(sp_test_compare(tst, hash) == SP_NOT_OK) {
        printf("Generated hash %s does not match reference hash %s\n", 
                tst->md5string, hash);
        fail = 1;
    }
    
    /* destroy functions here */

    if(fail) return SP_NOT_OK;
    else return SP_OK;
}
