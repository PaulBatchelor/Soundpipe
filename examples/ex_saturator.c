#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "soundpipe.h"

typedef struct {
    sp_saturator *saturator;
    sp_osc *osc;
    sp_ftbl *ft;
} UserData;

void process(sp_data *sp, void *udata) 
{
    UserData *ud = udata;
    SPFLOAT osc = 0, saturator = 0;
    sp_osc_compute(sp, ud->osc, NULL, &osc);
    sp_saturator_compute(sp, ud->saturator, &osc, &saturator);
    sp->out[0] = saturator;
}

int main() 
{
    srand(1234567);
    UserData ud;
    sp_data *sp;
    sp_create(&sp);

    sp_saturator_create(&ud.saturator);
    sp_osc_create(&ud.osc);
    sp_ftbl_create(sp, &ud.ft, 2048);
    sp_saturator_init(sp, ud.saturator);
    sp_gen_sine(sp, ud.ft);
    sp_osc_init(sp, ud.osc, ud.ft, 0);
    ud.saturator->drive = 20;
    ud.saturator->dcOffset = 4;
    ud.osc->amp = 0.5;
    sp->len = 44100 * 5;
    sp_process(sp, &ud, process);

    sp_saturator_destroy(&ud.saturator);
    sp_ftbl_destroy(&ud.ft);
    sp_osc_destroy(&ud.osc);

    sp_destroy(&sp);
    return 0;
}
