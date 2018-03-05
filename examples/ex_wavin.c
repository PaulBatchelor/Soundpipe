#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "soundpipe.h"

typedef struct {
    sp_wavin *wavin;
} UserData;

void process(sp_data *sp, void *udata) {
    UserData *ud = udata;
    SPFLOAT wavin = 0;
    sp_wavin_compute(sp, ud->wavin, NULL, &wavin);
    sp->out[0] = wavin;
}

int main() {
    UserData ud;
    sp_data *sp;
    sp_create(&sp);
    sp_srand(sp, 1234567);

    sp_wavin_create(&ud.wavin);

    sp_wavin_init(sp, ud.wavin, "oneart.wav");

    sp->len = 44100 * 5;
    sp_process(sp, &ud, process);

    sp_wavin_destroy(&ud.wavin);

    sp_destroy(&sp);
    return 0;
}
