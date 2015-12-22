#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "soundpipe.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

int t_saw(sp_test *tst, sp_data *sp, const char *hash) {
    uint32_t n;
    int fail = 0;
    SPFLOAT saw;
    sp_saw *saw_d;

    sp_saw_create(&saw_d);

    sp_saw_init(sp, saw_d);
    *saw_d->freq = 500;
    sp->len = 44100 * 5;

    for(n = 0; n < tst->size; n++) {
        saw = 0;
        sp_saw_compute(sp, saw_d, NULL, &saw);
        sp_out(sp, 0, saw);
        sp_test_add_sample(tst, sp->out[0]);
    }

    fail = sp_test_verify(tst, hash);

    sp_saw_destroy(&saw_d);

    if(fail) return SP_NOT_OK;
    else return SP_OK;
}

