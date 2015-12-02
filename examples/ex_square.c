#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "soundpipe.h"

typedef struct {
    sp_square *square;
    int counter;
} UserData;

void process(sp_data *sp, void *udata) {
    UserData *ud = udata;
    if(ud->counter == 0){
        *ud->square->freq = 500 + rand() % 2000;
    }
    sp_square_compute(sp, ud->square, NULL, &sp->out[0]);
    ud->counter = (ud->counter + 1) % 4410;
}

int main() {
    srand(time(NULL));
    UserData ud;
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
