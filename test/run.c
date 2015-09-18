#include <stdlib.h>
#include <stdio.h>
#include "soundpipe.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

#define TEST(str, desc, md5hash) int str(sp_test *tst, sp_data *sp, const char *hash);
#include "all_tests.h"
#undef TEST

#define SIZE(x) sizeof(x) / sizeof(*x)

typedef struct {
    sp_data *sp;
    uint32_t size;
} test_data;

int main() 
{
    uint32_t n;
    sp_test_entry tests [] = {
#define TEST(str, desc, md5hash) {str, desc, md5hash}, 
#include "all_tests.h"
#undef TEST
    };

    plan(SIZE(tests));
    sp_test *tst;
    sp_data *sp;
    sp_create(&sp);

    uint32_t size = 44100 * 5;

    for(n = 0; n < SIZE(tests); n++) {
        sp_test_create(&tst, size);
        ok(tests[n].func(tst, sp, tests[n].hash)  == SP_OK, tests[n].desc);
#ifdef WRITE_RAW
        if(n != 0) sp_test_write_raw(tst, n);
#endif
        sp_test_destroy(&tst);
    }

    sp_destroy(&sp);
    return 0;
}
