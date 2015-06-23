#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "soundpipe.h"

typedef struct {
    sp_osc *osc;
    sp_ftbl *ft; 
    sp_tevent *te;
    int counter;
    SPFLOAT freq;
} udata;

void write_osc(sp_data *data, void *ud) {
    udata *udp = ud;
    SPFLOAT trig = 0;
    if(udp->counter == 0){
        trig = 1.0;
    }
    sp_tevent_compute(data, udp->te, &trig, &udp->osc->freq);
    sp_osc_compute(data, udp->osc, NULL, &data->out[0]);
    udp->counter = (udp->counter + 1) % 4410;
}

void freq_reinit(void *ud){
    SPFLOAT *freq = ud;
    *freq = 500 + rand() % 2000;
}

void freq_compute(void *ud, SPFLOAT *out){
    SPFLOAT *freq = ud;
    *out = *freq;
}

int main() {
    srand(time(NULL));
    udata ud;
    SPFLOAT *freqp = &ud.freq;
    ud.counter = 0;
    ud.freq = 400;
    sp_data *sp;
    sp_create(&sp);
    sp_tevent_create(&ud.te);
    sp_ftbl_create(sp, &ud.ft, 2048);
    sp_osc_create(&ud.osc);

    sp_tevent_init(sp, ud.te, freq_reinit, freq_compute, freqp);
    sp_gen_sine(ud.ft);
    sp_osc_init(sp, ud.osc, ud.ft);
    ud.osc->freq = *freqp;
    sp_gen_sine(ud.ft);
    sp->len = 44100 * 5;
    sp_process(sp, &ud, write_osc);

    sp_ftbl_destroy(&ud.ft);
    sp_osc_destroy(&ud.osc);
    sp_tevent_destroy(&ud.te);
    sp_destroy(&sp);
    return 0;
}
