#include "soundpipe.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    sp_spa *wav;
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
    sp_spa_create(&dt.wav);
    sp_spa_init(sp, dt.wav, SAMPDIR "oneart.spa");


    for(n = 0; n < tst->size; n++) {
        sp_spa_compute(sp, dt.wav, NULL, &diskin);
        sp_lpc_compute(sp, dt.lpc, &diskin, &out);

        sp_test_add_sample(tst, out);
    }

    fail = sp_test_verify(tst, hash);

    sp_spa_destroy(&dt.wav);
    sp_lpc_destroy(&dt.lpc);

    if(fail) return SP_NOT_OK;
    else return SP_OK;
}
