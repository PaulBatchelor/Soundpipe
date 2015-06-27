#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "soundpipe.h"

typedef struct {
    sp_osc *osc[3];
    sp_ftbl *ft; 
} udata;

void write_osc(sp_data *sp, void *ud) {
    udata *udp = ud;
    int i;
    SPFLOAT out = 0, osc = 0;
    for(i = 0; i < 3; i++) {
       sp_osc_compute(sp, udp->osc[i], NULL, &osc);
       out += osc * 0.2;
    }
    sp->out[0] = out;
}

int main() {
    srand(time(NULL));
    int i;
    udata ud;
    sp_data *sp;
    sp_create(&sp);
    sp_ftbl_create(sp, &ud.ft, 4096);
    for(i = 0; i < 3; i++) sp_osc_create(&ud.osc[i]);

    sp_gen_line(sp, ud.ft, "1 4096 -1");
    sp_osc_init(sp, ud.osc[0], ud.ft);
    ud.osc[0]->freq = sp_midi2cps(48 - 0.05);
    sp_osc_init(sp, ud.osc[1], ud.ft);
    ud.osc[1]->freq = sp_midi2cps(48 - 12);
    sp_osc_init(sp, ud.osc[2], ud.ft);
    ud.osc[2]->freq = sp_midi2cps(48 + 0.05);
    sp->len = 44100 * 5;
    sp_process(sp, &ud, write_osc);

    sp_ftbl_destroy(&ud.ft);
    for(i = 0; i < 3; i++) sp_osc_destroy(&ud.osc[i]);
    sp_destroy(&sp);
    return 0;
}
