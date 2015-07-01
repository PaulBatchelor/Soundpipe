#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "soundpipe.h"

typedef struct {
    sp_noise *ns;
    sp_butbp *butbp;
    int counter;
} udata;

void write_noise(sp_data *data, void *ud) {
    udata *udata = ud;
    SPFLOAT in = 0;
    SPFLOAT out = 0;
    if(udata->counter == 0) {
        udata->butbp->freq= 500 + rand() % 4000;
    }
    sp_noise_compute(data, udata->ns, NULL, &in);
    sp_butbp_compute(data, udata->butbp, &in, &data->out[0]); 
    udata->counter = (udata->counter + 1) % 5000;
}
int main() {
    srand(time(NULL));
    udata ud;
    ud.counter = 0;
    sp_data *sp;
    sp_create(&sp);
    sp_noise_create(&ud.ns);
    sp_butbp_create(&ud.butbp);
    sp_noise_init(sp, ud.ns);
    sp_butbp_init(sp, ud.butbp);
    sp->len = 44100 * 5;
    sp_process(sp, &ud, write_noise);
    sp_noise_destroy(&ud.ns);
    sp_butbp_destroy(&ud.butbp);
    sp_destroy(&sp);
    return 0;
}
