#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "soundpipe.h"

typedef struct {
    sp_triangle *triangle;
    int counter;
} udata;

void process(sp_data *data, void *ud) {
    udata *udp = ud;
    if(udp->counter == 0){
        *udp->triangle->freq = 500 + rand() % 2000;
    }
    sp_triangle_compute(data, udp->triangle, NULL, &data->out[0]);
    udp->counter = (udp->counter + 1) % 4410;
}

int main() {
    srand(time(NULL));
    udata ud;
    ud.counter = 0;
    sp_data *sp;
    sp_create(&sp);
    
    sp_triangle_create(&ud.triangle);

    sp_triangle_init(sp, ud.triangle);
    *ud.triangle->freq = 500.0;
    *ud.triangle->amp = 0.9;
    sp->len = 44100 * 5;
    sp_process(sp, &ud, process);

    sp_triangle_destroy(&ud.triangle);
    sp_destroy(&sp);
    return 0;
}
