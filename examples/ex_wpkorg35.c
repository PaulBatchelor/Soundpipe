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
    sp_wpkorg35 *wpkorg35;
    sp_noise *noise;
} UserData;

void process(sp_data *sp, void *udata) {
    UserData *ud = udata;
    SPFLOAT noise = 0, wpkorg35 = 0;
    sp_noise_compute(sp, ud->noise, NULL, &noise);
    sp_wpkorg35_compute(sp, ud->wpkorg35, &noise, &wpkorg35);
    sp->out[0] = wpkorg35;
}

int main() {
    srand(1234567);
    UserData ud;
    sp_data *sp;
    sp_create(&sp);

    sp_wpkorg35_create(&ud.wpkorg35);
    sp_noise_create(&ud.noise);

    sp_wpkorg35_init(sp, ud.wpkorg35);
    sp_noise_init(sp, ud.noise);

    sp->len = 44100 * 5;
    sp_process(sp, &ud, process);

    sp_wpkorg35_destroy(&ud.wpkorg35);
    sp_noise_destroy(&ud.noise);

    sp_destroy(&sp);
    return 0;
}
