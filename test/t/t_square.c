#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "soundpipe.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

int t_square(sp_test *tst, sp_data *sp, const char *hash) {
    uint32_t n;
    int fail = 0;
    SPFLOAT square;
    sp_square *square_d;

    sp_square_create(&square_d);

    sp_square_init(sp, square_d);
    *square_d->freq = 500;
    *square_d->width = 0.4;
    sp->len = 44100 * 5;

    for(n = 0; n < tst->size; n++) {
        square = 0;
        sp_square_compute(sp, square_d, NULL, &square);
        sp_out(sp, 0, square);
        sp_test_add_sample(tst, sp->out[0]);
    }

    fail = sp_test_verify(tst, hash);

    sp_square_destroy(&square_d);

    if(fail) return SP_NOT_OK;
    else return SP_OK;
}

