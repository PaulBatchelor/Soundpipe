#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "soundpipe.h"

typedef struct {
    sp_triangle *triangle;
    int counter;
} UserData;

void process(sp_data *sp, void *udata) {
    UserData *ud = udata;
    if(ud->counter == 0){
        *ud->triangle->freq = 500 + rand() % 2000;
    }
    sp_triangle_compute(sp, ud->triangle, NULL, &sp->out[0]);
    ud->counter = (ud->counter + 1) % 4410;
}

int main() {
    srand(time(NULL));
    UserData ud;
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
