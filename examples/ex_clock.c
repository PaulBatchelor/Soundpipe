/*
 * This is a dummy example.
 * Please implement a small and simple working example of your module, and then
 * remove this header.
 * Don't be clever.
 * Bonus points for musicality. 
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "soundpipe.h"

typedef struct {
    sp_clock *clock;
    sp_osc *osc;
    sp_ftbl *ft; 
    sp_tenv *te;
} UserData;

void process(sp_data *sp, void *udata) {
    UserData *ud = udata;
    SPFLOAT osc = 0, clock = 0, env = 0;
    SPFLOAT trig = 0;
    sp_osc_compute(sp, ud->osc, NULL, &osc);
    sp_clock_compute(sp, ud->clock, &trig, &clock);
    sp_tenv_compute(sp, ud->te, &clock, &env);
    sp_out(sp, 0, env * osc);
}

int main() {
    UserData ud;
    sp_data *sp;
    sp_create(&sp);
    sp_srand(sp, 1234567);

    sp_clock_create(&ud.clock);
    sp_osc_create(&ud.osc);
    sp_ftbl_create(sp, &ud.ft, 2048);
    sp_tenv_create(&ud.te);

    sp_clock_init(sp, ud.clock);
    ud.clock->bpm = 130;
    ud.clock->subdiv = 4;
    sp_gen_sine(sp, ud.ft);
    sp_osc_init(sp, ud.osc, ud.ft, 0);
    sp_tenv_init(sp, ud.te);
    ud.te->atk = 0.001;
    ud.te->hold = 0.001;
    ud.te->rel = 0.001;
    

    sp->len = 44100 * 5;
    sp_process(sp, &ud, process);

    sp_clock_destroy(&ud.clock);
    sp_ftbl_destroy(&ud.ft);
    sp_osc_destroy(&ud.osc);
    sp_tenv_destroy(&ud.te);

    sp_destroy(&sp);
    return 0;
}
