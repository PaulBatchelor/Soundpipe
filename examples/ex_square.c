#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "soundpipe.h"

typedef struct {
    sp_square *square;
    int counter;
} udata;

void process(sp_data *data, void *ud) {
    udata *udp = ud;
    if(udp->counter == 0){
        *udp->square->freq = 500 + rand() % 2000;
    }
    sp_square_compute(data, udp->square, NULL, &data->out[0]);
    udp->counter = (udp->counter + 1) % 4410;
}

int main() {
    srand(time(NULL));
    udata ud;
    ud.counter = 0;
    sp_data *sp;
    sp_create(&sp);
    
    sp_square_create(&ud.square);

    sp_square_init(sp, ud.square);
    *ud.square->freq = 500.0;
    *ud.square->amp = 0.9;
    *ud.square->width = 0.5;
    sp->len = 44100 * 5;
    sp_process(sp, &ud, process);

    sp_square_destroy(&ud.square);
    sp_destroy(&sp);
    return 0;
}
