#include "soundpipe.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    sp_noise *ns;
    sp_tone *tn;
} udata;

int t_tone(sp_test *tst, sp_data *sp, const char *hash) 
{
    uint32_t n;
    int fail = 0;

    udata ud;
    sp_noise_create(&ud.ns);
    sp_tone_create(&ud.tn);
    sp_noise_init(sp, ud.ns);
    sp_tone_init(sp, ud.tn);

    SPFLOAT in;
    SPFLOAT out;

    for(n = 0; n < tst->size; n++) {
        sp_noise_compute(sp, ud.ns, NULL, &in);
        sp_tone_compute(sp, ud.tn, &in, &sp->out[0]); 
        sp_test_add_sample(tst, sp->out[0]);
    }

    if(sp_test_compare(tst, hash) == SP_NOT_OK) {
        printf("Generated hash %s does not match reference hash %s\n", 
                tst->md5string, hash);
        fail = 1;
    }
     
    sp_tone_destroy(&ud.tn);
    sp_noise_destroy(&ud.ns);

    if(fail) return SP_NOT_OK;
    else return SP_OK;
}
