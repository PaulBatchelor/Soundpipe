#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "soundpipe.h"

typedef struct {
    sp_diskin *disk;
    sp_zita *rev;
    int counter;
} UserData;

void process(sp_data *sp , void *udata) {
    UserData *ud = udata;
    SPFLOAT in = 0;
    SPFLOAT out = 0;
    SPFLOAT foo = 0;

    sp_diskin_compute(sp, ud->disk, NULL, &in);
    sp_zita_compute(sp, ud->rev, &in, &in, &sp->out[0], &foo);
}

int main() {
    srand(time(NULL));
    UserData ud;
    ud.counter = 0;
    sp_data *sp;
    sp_create(&sp);
    sp_diskin_create(&ud.disk);
    sp_zita_create(&ud.rev);

    sp_diskin_init(sp, ud.disk, "oneart.wav");
    sp_zita_init(sp, ud.rev);

    sp->len = 44100 * 5;
    sp_process(sp, &ud, process);

    sp_diskin_destroy(&ud.disk);
    sp_zita_destroy(&ud.rev);
    sp_destroy(&sp);
    return 0;
}
