#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "soundpipe.h"

typedef struct {
    sp_brown *brown;
} UserData;

void process(sp_data *sp, void *udata) {
    UserData *ud = udata;
    SPFLOAT brown = 0;
    sp_brown_compute(sp, ud->brown, NULL, &brown);
    sp->out[0] = brown;
}

int main() {
    UserData ud;
    sp_data *sp;
    sp_create(&sp);
    sp_srand(sp, 1234567);

    sp_brown_create(&ud.brown);

    sp_brown_init(sp, ud.brown);

    sp->len = 44100 * 5;
    sp_process(sp, &ud, process);

    sp_brown_destroy(&ud.brown);

    sp_destroy(&sp);
    return 0;
}
