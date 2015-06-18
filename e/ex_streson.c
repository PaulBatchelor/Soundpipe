#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "soundpipe.h"

typedef struct {
    sp_noise *ns;
    sp_streson *stres;
} udata;

void write_noise(sp_data *data, void *ud) {
    udata *udata = ud;
    SPFLOAT in = 0;
    SPFLOAT noise = 0;
    sp_noise_compute(data, udata->ns, NULL, &noise);
    sp_streson_compute(data, udata->stres, &noise, &data->out);
}
int main() {
    srand(time(NULL));
    udata ud;
    sp_data *sp;
    sp_create(&sp);
    sp_streson_create(&ud.stres);
    sp_noise_create(&ud.ns);
    sp_noise_init(sp, ud.ns);
    sp_streson_init(sp, ud.stres);
    sp->len = 44100 * 5;
    sp_process(sp, &ud, write_noise);
    sp_noise_destroy(&ud.ns);
    sp_streson_destroy(&ud.stres);
    sp_destroy(&sp);
    return 0;
}
