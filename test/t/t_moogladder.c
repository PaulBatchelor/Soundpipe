#include "soundpipe.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    sp_noise *ns;
    sp_moogladder *moog;
    int counter;
} udata;

int t_moogladder(sp_test *tst, sp_data *sp, const char *hash) 
{
    sp_srand(sp, 0); 
    uint32_t n;
    int fail = 0;

    udata ud;
    ud.counter = 0;
    sp_noise_create(&ud.ns);
    sp_moogladder_create(&ud.moog);
    sp_noise_init(sp, ud.ns);
    sp_moogladder_init(sp, ud.moog);

    SPFLOAT in;
    SPFLOAT out;

    for(n = 0; n < tst->size; n++) {
        in = 0;
        out = 0;

        if(ud.counter == 0) {
            ud.moog->res = 0.8;
            ud.moog->freq = 500 + sp_rand(sp) % 4000;
        }

        sp_noise_compute(sp, ud.ns, NULL, &in);
        sp_moogladder_compute(sp, ud.moog, &in, &sp->out[0]); 
        ud.counter = (ud.counter + 1) % 5000;

        sp_test_add_sample(tst, sp->out[0]);
    }

    if(sp_test_compare(tst, hash) == SP_NOT_OK) {
        printf("Generated hash %s does not match reference hash %s\n", 
                tst->md5string, hash);
        fail = 1;
    }
 
    sp_noise_destroy(&ud.ns);
    sp_moogladder_destroy(&ud.moog);

    if(fail) return SP_NOT_OK;
    else return SP_OK;
}
