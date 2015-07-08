#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "soundpipe.h"

typedef struct {
    sp_noise *ns;
    sp_reson *reson;
    int counter;
} udata;

void write_noise(sp_data *data, void *ud) {
    udata *udata = ud;
    SPFLOAT in = 0;
    SPFLOAT out = 0;
    if(udata->counter == 0) {
        if(udata->reson->cutoff >= 5000) {
            udata->reson->cutoff -= 4000;
        }
        if(udata->reson->bw <= 20) {
            udata->reson->bw += 500;
        }
        udata->reson->cutoff += 100; 
        udata->reson->bw -= 20; 
    }
    sp_noise_compute(data, udata->ns, NULL, &in);
    sp_reson_compute(data, udata->reson, &in, &out); 
    data->out[0] = out * 0.1;
    udata->counter = (udata->counter + 1) % 5000;
}
int main() {
    srand(time(NULL));
    udata ud;
    ud.counter = 0;
    sp_data *sp;
    sp_create(&sp);
    sp_noise_create(&ud.ns);
    sp_reson_create(&ud.reson);
    sp_noise_init(sp, ud.ns);
    sp_reson_init(sp, ud.reson, 4000, 1000);
    sp->len = 44100 * 5;
    sp_process(sp, &ud, write_noise);
    sp_noise_destroy(&ud.ns);
    sp_reson_destroy(&ud.reson);
    sp_destroy(&sp);
    return 0;
}
