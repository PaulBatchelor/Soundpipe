#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "soundpipe.h"

typedef struct {
    sp_saw *saw;
    int counter;
} UserData;

void process(sp_data *sp, void *udata) {
    UserData *ud = udata;
    if(ud->counter == 0){
        *ud->saw->freq = 500 + rand() % 2000;
    }
    sp_saw_compute(sp, ud->saw, NULL, &sp->out[0]);
    ud->counter = (ud->counter + 1) % 4410;
}

int main() {
    srand(time(NULL));
    UserData ud;
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
