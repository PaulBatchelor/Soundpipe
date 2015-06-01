#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "soundpipe.h"

typedef struct {
    sp_noise *ns;
    sp_revsc *rev;
    int counter;
} udata;

void write_noise(sp_data *data, void *ud) {
    udata *udata = ud;
    SPFLOAT in = 0;
    SPFLOAT out = 0;
    sp_noise_compute(data, udata->ns, NULL, &in);
    
    if(udata->counter < 2000) {
        udata->counter = (udata->counter + 1) % 5000;
    }else{
        in = 0;
    }
    sp_revsc_compute(data, udata->rev, &in, &data->out); 
}
int main() {
    srand(time(NULL));
    udata ud;
    ud.counter = 0;
    sp_auxdata rev_aux;
    sp_data *sp;
    sp_create(&sp);
    sp_noise_create(&ud.ns);
    sp_revsc_alloc(sp, &rev_aux);
    sp_revsc_create(sp, &ud.rev);
    sp_noise_init(sp, ud.ns);
    sp_revsc_init(sp, ud.rev, &rev_aux);

    //sp->len = 3;
    sp->len = 44100 * 5;
    sp_process(sp, &ud, write_noise);

    sp_noise_destroy(&ud.ns);
    sp_revsc_destroy(&ud.rev, &rev_aux);
    sp_destroy(&sp);
    return 0;
}
