#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "soundpipe.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

int t_triangle(sp_test *tst, sp_data *sp, const char *hash) {
    uint32_t n;
    int fail = 0;
    SPFLOAT triangle;
    sp_triangle *triangle_d;

    sp_triangle_create(&triangle_d);

    sp_triangle_init(sp, triangle_d);
    *triangle_d->freq = 500;
    sp->len = 44100 * 5;

    for(n = 0; n < tst->size; n++) {
        triangle = 0;
        sp_triangle_compute(sp, triangle_d, NULL, &triangle);
        sp_out(sp, 0, triangle);
        sp_test_add_sample(tst, sp->out[0]);
    }

    fail = sp_test_verify(tst, hash);

    sp_triangle_destroy(&triangle_d);

    if(fail) return SP_NOT_OK;
    else return SP_OK;
}

