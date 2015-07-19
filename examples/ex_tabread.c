#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "soundpipe.h"

typedef struct {
    sp_tabread *tr;
    sp_ftbl *ft;
} UserData;

void process(sp_data *sp, void *udata) {
    UserData *ud = udata;
    SPFLOAT tab = 0.0;
    sp_tabread_compute(sp, ud->tr, NULL, &tab);
    sp->out[0] = tab;
}

int main() {
    srand(time(NULL));
    UserData ud;
    sp_data *sp;
    sp_create(&sp);

    sp_tabread_create(&ud.tr);

    sp_ftbl_create(sp, &ud.ft, 395393);
    sp_gen_file(sp, ud.ft, "oneart.wav");

    sp_tabread_init(sp, ud.tr, ud.ft);
    sp->len = 44100 * 5;
    sp_process(sp, &ud, process);

    sp_tabread_destroy(&ud.tr);
    sp_ftbl_destroy(&ud.ft);
    sp_destroy(&sp);
    return 0;
}
