#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "soundpipe.h"

typedef struct {
    sp_pinknoise *ns;
} udata;

void write_pinknoise(sp_data *data, void *ud) {
    udata *udata = ud;
    SPFLOAT in = 0;
    sp_pinknoise_compute(data, udata->ns, NULL, &data->out[0]);
}

int main() {
    srand(time(NULL));
    udata ud;
    sp_data *sp;
    sp_create(&sp);
    sp_pinknoise_create(&ud.ns);
    sp_pinknoise_init(sp, ud.ns);
    sp->len = 44100 * 5;
    sp_process(sp, &ud, write_pinknoise);
    sp_pinknoise_destroy(&ud.ns);
    sp_destroy(&sp);
    return 0;
}
