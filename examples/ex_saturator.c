#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "soundpipe.h"

typedef struct {
    sp_saturator *saturator;
    sp_diskin *diskin;
    sp_dcblock *dcblk;
} UserData;

void process(sp_data *sp, void *udata) 
{
    UserData *ud = udata;
    SPFLOAT diskin = 0, saturator = 0, dcblk = 0;
    sp_diskin_compute(sp, ud->diskin, NULL, &diskin);
    sp_saturator_compute(sp, ud->saturator, &diskin, &saturator);
    sp_dcblock_compute(sp, ud->dcblk, &saturator, &dcblk);
    sp_out(sp, 0, dcblk);
}

int main() 
{
    UserData ud;
    sp_data *sp;
    sp_create(&sp);
    sp_srand(sp, 1234567);

    sp_saturator_create(&ud.saturator);
    sp_diskin_create(&ud.diskin);
    sp_dcblock_create(&ud.dcblk);

    sp_saturator_init(sp, ud.saturator);
    sp_diskin_init(sp, ud.diskin, "oneart.wav");
    sp_dcblock_init(sp, ud.dcblk);

    ud.saturator->drive = 10;
    ud.saturator->dcoffset = 4;
    sp->len = 44100 * 5;
    sp_process(sp, &ud, process);

    sp_saturator_destroy(&ud.saturator);
    sp_diskin_destroy(&ud.diskin);
    sp_dcblock_destroy(&ud.dcblk);

    sp_destroy(&sp);
    return 0;
}
