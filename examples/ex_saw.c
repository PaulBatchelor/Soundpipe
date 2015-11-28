#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "soundpipe.h"

typedef struct {
    sp_saw *saw;
    int counter;
} udata;

void process(sp_data *data, void *ud) {
    udata *udp = ud;
    if(udp->counter == 0){
        *udp->saw->freq = 500 + rand() % 2000;
    }
    sp_saw_compute(data, udp->saw, NULL, &data->out[0]);
    udp->counter = (udp->counter + 1) % 4410;
}

int main() {
    srand(time(NULL));
    udata ud;
    ud.counter = 0;
    sp_data *sp;
    sp_create(&sp);
    
    sp_saw_create(&ud.saw);

    sp_saw_init(sp, ud.saw);
    *ud.saw->freq = 500;
    *ud.saw->amp = 1;
    sp->len = 44100 * 5;
    sp_process(sp, &ud, process);

    sp_saw_destroy(&ud.saw);
    sp_destroy(&sp);
    return 0;
}
