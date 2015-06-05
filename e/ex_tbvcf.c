#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "soundpipe.h"

typedef struct {
    sp_noise *ns;
    sp_tbvcf *tn;
} udata;

void write_noise(sp_data *data, void *ud) {
    udata *udata = ud;
    SPFLOAT in = 0;
    SPFLOAT out = 0;
    sp_noise_compute(data, udata->ns, NULL, &in);
    sp_tbvcf_compute(data, udata->tn, &in, &data->out); 
}
int main() {
    srand(time(NULL));
    udata ud;
    sp_data *sp;
    sp_create(&sp);
    sp_noise_create(&ud.ns);
    sp_tbvcf_create(&ud.tn);
    sp_noise_init(sp, ud.ns);
    sp_tbvcf_init(sp, ud.tn);
    sp->len = 44100 * 5;
    ud.tn->dist = 1.0;
    sp_process(sp, &ud, write_noise);
    sp_noise_destroy(&ud.ns);
    sp_tbvcf_destroy(&ud.tn);
    sp_destroy(&sp);
    return 0;
}
