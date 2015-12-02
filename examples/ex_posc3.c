#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "soundpipe.h"

typedef struct {
    sp_posc3 *posc3;
    sp_ftbl *ft; 
    int counter;
} UserData;

void write_posc3(sp_data *data, void *ud) {
    UserData *udp = ud;
    if(udp->counter == 0){
        udp->posc3->freq = 500 + rand() % 2000;
    }
    sp_posc3_compute(data, udp->posc3, NULL, &data->out[0]);
    udp->counter = (udp->counter + 1) % 4410;
}

int main() {
    srand(time(NULL));
    UserData ud;
    ud.counter = 0;
    sp_data *sp;
    sp_create(&sp);
    sp_ftbl_create(sp, &ud.ft, 1024);
    sp_posc3_create(&ud.posc3);

    sp_gen_sine(sp, ud.ft);
    sp_posc3_init(sp, ud.posc3, ud.ft);
    ud.posc3->freq = 500;
    sp->len = 44100 * 5;
    sp_process(sp, &ud, write_posc3);

    sp_ftbl_destroy(&ud.ft);
    sp_posc3_destroy(&ud.posc3);
    sp_destroy(&sp);
    return 0;
}
