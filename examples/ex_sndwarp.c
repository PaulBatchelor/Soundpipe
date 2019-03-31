#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "soundpipe.h"

typedef struct {
    sp_sndwarp *sndwarp;
    sp_ftbl *win;
    sp_ftbl *wav;
} UserData;

void process(sp_data *sp, void *udata) {
    UserData *ud = udata;
    SPFLOAT osc = 0, sndwarp = 0;
    sp_sndwarp_compute(sp, ud->sndwarp, NULL, &sndwarp);
    sp->out[0] = sndwarp;
}

int main() {
    UserData ud;
    sp_data *sp;
    sp_create(&sp);
    sp_srand(sp, 1234567);

    sp_sndwarp_create(&ud.sndwarp);
    sp_ftbl_create(sp, &ud.win, 4096);

    sp_ftbl_loadfile(sp, &ud.wav, "oneart.wav");
    sp_gen_composite(sp, ud.win, "0.5 1 0 0.5");
    sp_sndwarp_init(sp,
                    ud.sndwarp,
                    ud.wav,
                    0,
                    4410,
                    882,
                    5,
                    ud.win,
                    1);

    sp->len = 44100 * 10;
    sp_process(sp, &ud, process);

    sp_sndwarp_destroy(&ud.sndwarp);
    sp_ftbl_destroy(&ud.wav);
    sp_ftbl_destroy(&ud.win);

    sp_destroy(&sp);
    return 0;
}
