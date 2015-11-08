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
    sp_mincer *mincer;
    sp_ftbl *ft; 
    sp_randi *randi;
} UserData;

void process(sp_data *sp, void *udata) {
    UserData *ud = udata;
    SPFLOAT osc = 0, mincer = 0, randi = 0;
   
    
    sp_randi_compute(sp, ud->randi, NULL, &randi);
    ud->mincer->time = randi;
    ud->mincer->amp = 1;
    ud->mincer->pitch = 1;
    sp_mincer_compute(sp, ud->mincer, NULL, &mincer);
    sp->out[0] = mincer;
}

int main() {
    UserData ud;
    sp_data *sp;
    sp_create(&sp);
    sp_srand(sp, 1234567);

    sp_mincer_create(&ud.mincer);
    sp_ftbl_create(sp, &ud.ft, 395393);

    sp_randi_create(&ud.randi);

    sp_gen_file(sp, ud.ft, "oneart.wav");
    sp_mincer_init(sp, ud.mincer, ud.ft);
    sp_randi_init(sp, ud.randi);
    ud.randi->min = 0;
    ud.randi->max = 5;
    ud.randi->cps = 1;

    sp->len = 44100 * 5;
    sp_process(sp, &ud, process);

    sp_mincer_destroy(&ud.mincer);
    sp_ftbl_destroy(&ud.ft);
    sp_randi_destroy(&ud.randi);

    sp_destroy(&sp);
    return 0;
}
