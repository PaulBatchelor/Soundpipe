#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "soundpipe.h"

typedef struct {
    sp_vco *vco;
} UserData;

void process(sp_data *sp, void *udata) {
    UserData *ud = udata;
    sp_vco_compute(sp, ud->vco, NULL, &sp->out[0]);
}

int main() {
    UserData ud;
    sp_data *sp;
    sp_create(&sp);
    sp_vco_create(&ud.vco);

    sp_vco_init(sp, ud.vco);
    sp->len = 44100 * 5;
    sp_process(sp, &ud, process);

    sp_vco_destroy(&ud.vco);
    sp_destroy(&sp);
    return 0;
}
