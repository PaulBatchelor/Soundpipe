#include <stdlib.h>
#include "soundpipe.h"

typedef struct {
    sp_diskin *wav;
    sp_lpc *lpc;
} user_data;

static void process(sp_data *sp, void *ud)
{
    user_data *dt;
    SPFLOAT diskin;
    SPFLOAT out;
    dt = ud;

    sp_diskin_compute(sp, dt->wav, NULL, &diskin);
    sp_lpc_compute(sp, dt->lpc, &diskin, &out);


    sp_out(sp, 0, out);
}

int main(int argc, char **argv)
{
    user_data dt;
    sp_data *sp;

    sp_create(&sp);
    sp->sr = 44100;
    sp->len = sp->sr * 8;

    sp_lpc_create(&dt.lpc);
    sp_lpc_init(sp, dt.lpc, 512);

    sp_diskin_create(&dt.wav);
    sp_diskin_init(sp, dt.wav, "oneart.wav");


    sp_process(sp, &dt, process);
    sp_diskin_destroy(&dt.wav);
    sp_lpc_destroy(&dt.lpc);
    sp_destroy(&sp);
    return 0;
}
