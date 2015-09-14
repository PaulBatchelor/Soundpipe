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
    sp_bar *bar;
    sp_osc *osc;
    sp_ftbl *ft; 
} UserData;

void process(sp_data *sp, void *udata) {
    UserData *ud = udata;
    SPFLOAT osc = 0, bar = 0;
    sp_osc_compute(sp, ud->osc, NULL, &osc);
    sp_bar_compute(sp, ud->bar, &osc, &bar);
    sp->out[0] = bar;
}

int main() {
    srand(1234567);
    UserData ud;
    sp_data *sp;
    sp_create(&sp);

    sp_bar_create(&ud.bar);
    sp_osc_create(&ud.osc);
    sp_ftbl_create(sp, &ud.ft, 2048);

    sp_bar_init(sp, ud.bar);
    sp_gen_sine(sp, ud.ft);
    sp_osc_init(sp, ud.osc, ud.ft, 0);

    sp->len = 44100 * 5;
    sp_process(sp, &ud, process);

    sp_bar_destroy(&ud.bar);
    sp_ftbl_destroy(&ud.ft);
    sp_osc_destroy(&ud.osc);

    sp_destroy(&sp);
    return 0;
}
