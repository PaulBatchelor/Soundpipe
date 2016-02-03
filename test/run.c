#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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

int main(int argc, char *argv[])
{
    uint32_t n;
    sp_test_entry tests [] = {
#define TEST(str, desc, md5hash) {str, desc, md5hash}, 
#include "all_tests.h"
#undef TEST
    };

    int err = 0;
    plan(SIZE(tests));
    sp_test *tst;
    sp_data *sp;
    sp_create(&sp);

    uint32_t size = 44100 * 5;

    if(argc == 1) {
        for(n = 0; n < SIZE(tests); n++) {
            sp_test_create(&tst, size);
            ok(tests[n].func(tst, sp, tests[n].hash)  == SP_OK, tests[n].desc);
#ifdef WRITE_RAW
            if(n != 0) sp_test_write_raw(tst, n);
#endif
            sp_test_destroy(&tst);
        }
    } else {
        if (!strcmp(argv[1], "gen_header")) {
            for(n = 0; n < SIZE(tests); n++) {
                printf("TEST(t_%s, \"%s\", \"%s\")\n", 
                        tests[n].desc, tests[n].desc, tests[n].hash);
            }
        } else {
            fprintf(stderr, "Invalid command %s\n", argv[1]);
            err = 1;
        }
    } 
    sp_destroy(&sp);
    return err;
}
