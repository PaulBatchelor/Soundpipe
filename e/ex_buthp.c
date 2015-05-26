#include <stdlib.h>
#include <stdio.h>
#include "soundpipe.h"

typedef struct {
    sp_noise *ns;
    sp_buthp *buthp;
} udata;

void write_noise(sp_data *data, void *ud) {
    udata *udata = ud;
    SPFLOAT in = 0;
    SPFLOAT out = 0;
    sp_noise_compute(data, udata->ns, NULL, &in);
    sp_buthp_compute(data, udata->buthp, &in, &data->out); 
}
int main() {
    srand(time(NULL));
    udata ud;
    sp_data *sp;
    sp_create(&sp);
    sp_noise_create(&ud.ns);
    sp_buthp_create(&ud.buthp);
    sp_noise_init(sp, ud.ns);
    sp_buthp_init(sp, ud.buthp);
    ud.buthp->kfc = 5000;
    sp->len = 44100 * 5;
    sp_process(sp, &ud, write_noise);
    sp_noise_destroy(&ud.ns);
    sp_buthp_destroy(&ud.buthp);
    sp_destroy(&sp);
    return 0;
}
