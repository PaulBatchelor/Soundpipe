#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "soundpipe.h"

typedef struct {
    sp_decimator *decimator;
    sp_diskin *file;
    sp_ftbl *ft; 
} UserData;

void process(sp_data *sp, void *udata) {
    UserData *ud = udata;
    SPFLOAT disk = 0, decimator = 0;
    sp_diskin_compute(sp, ud->file, NULL, &disk);
    sp_decimator_compute(sp, ud->decimator, &disk, &decimator);
    sp->out[0] = decimator;
}

int main() {
    srand(1234567);
    UserData ud;
    sp_data *sp;
    sp_create(&sp);

    sp_decimator_create(&ud.decimator);
    sp_diskin_create(&ud.file);

    sp_diskin_init(sp, ud.file, "oneart.wav");
    sp_decimator_init(sp, ud.decimator);
    sp->len = 44100 * 5;
    sp_process(sp, &ud, process);

    sp_decimator_destroy(&ud.decimator);
    sp_diskin_destroy(&ud.file);

    sp_destroy(&sp);
    return 0;
}
