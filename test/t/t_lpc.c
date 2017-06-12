#include "soundpipe.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    sp_diskin *wav;
    sp_lpc *lpc;
} user_data;

int t_lpc(sp_test *tst, sp_data *sp, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    user_data dt;
    SPFLOAT diskin;
    SPFLOAT out;

    diskin = 0;
    out = 0;
    sp_lpc_create(&dt.lpc);
    sp_lpc_init(sp, dt.lpc, 512);
    sp_diskin_create(&dt.wav);
    sp_diskin_init(sp, dt.wav, SAMPDIR "oneart.wav");


    for(n = 0; n < tst->size; n++) {
        sp_diskin_compute(sp, dt.wav, NULL, &diskin);
        sp_lpc_compute(sp, dt.lpc, &diskin, &out);

        sp_test_add_sample(tst, out);
    }

    fail = sp_test_verify(tst, hash);

    sp_diskin_destroy(&dt.wav);
    sp_lpc_destroy(&dt.lpc);

    if(fail) return SP_NOT_OK;
    else return SP_OK;
}
