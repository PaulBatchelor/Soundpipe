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
    sp_mul *mul;
    sp_osc *osc1;
    sp_osc *osc2;
    sp_ftbl *ft;
} UserData;

void process(sp_data *sp, void *udata) {
    UserData *ud = udata;
    SPFLOAT osc1 = 0, osc2 = 0, mul = 0;
    sp_osc_compute(sp, ud->osc1, NULL, &osc1);
    sp_osc_compute(sp, ud->osc2, NULL, &osc2);
    sp_mul_compute(sp, ud->mul, &osc1, &osc2, &mul);
    sp->out[0] = mul;
}

int main() {
    srand(1234567);
    UserData ud;
    sp_data *sp;
    sp_create(&sp);

    sp_mul_create(&ud.mul);
    sp_osc_create(&ud.osc1);
    sp_osc_create(&ud.osc2);
    sp_ftbl_create(sp, &ud.ft, 2048);

    sp_mul_init(sp, ud.mul);
    sp_gen_sine(sp, ud.ft);
    sp_osc_init(sp, ud.osc1, ud.ft, 0);
    sp_osc_init(sp, ud.osc2, ud.ft, 0);

    ud.osc2->freq = 610;
    sp->len = 44100 * 5;
    sp_process(sp, &ud, process);

    sp_mul_destroy(&ud.mul);
    sp_ftbl_destroy(&ud.ft);
    sp_osc_destroy(&ud.osc1);
    sp_osc_destroy(&ud.osc2);

    sp_destroy(&sp);
    return 0;
}
