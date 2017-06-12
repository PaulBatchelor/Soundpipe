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
    sp_lpc *lpc;
    sp_osc *osc;
    sp_ftbl *ft; 
} UserData;

void process(sp_data *sp, void *udata) {
    UserData *ud = udata;
    SPFLOAT osc = 0, lpc = 0;
    sp_osc_compute(sp, ud->osc, NULL, &osc);
    sp_lpc_compute(sp, ud->lpc, &osc, &lpc);
    sp->out[0] = lpc;
}

int main() {
    UserData ud;
    sp_data *sp;
    sp_create(&sp);
    sp_srand(sp, 1234567);

    sp_lpc_create(&ud.lpc);
    sp_osc_create(&ud.osc);
    sp_ftbl_create(sp, &ud.ft, 2048);

    sp_lpc_init(sp, ud.lpc);
    sp_gen_sine(sp, ud.ft);
    sp_osc_init(sp, ud.osc, ud.ft, 0);

    sp->len = 44100 * 5;
    sp_process(sp, &ud, process);

    sp_lpc_destroy(&ud.lpc);
    sp_ftbl_destroy(&ud.ft);
    sp_osc_destroy(&ud.osc);

    sp_destroy(&sp);
    return 0;
}
