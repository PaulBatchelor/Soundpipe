#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "soundpipe.h"

typedef struct {
    sp_spa *spa;
} UserData;

void process(sp_data *sp, void *udata) {
    UserData *ud = udata;
    SPFLOAT spa = 0;
    sp_spa_compute(sp, ud->spa, NULL, &spa);
    sp->out[0] = spa;
}

int main() {
    UserData ud;
    sp_data *sp;
    sp_create(&sp);
    sp_srand(sp, 1234567);

    sp_spa_create(&ud.spa);

    sp_spa_init(sp, ud.spa, "oneart.spa");

    sp->len = 44100 * 10;
    sp_process(sp, &ud, process);

    sp_spa_destroy(&ud.spa);

    sp_destroy(&sp);
    return 0;
}
