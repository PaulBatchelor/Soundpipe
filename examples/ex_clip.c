#include <stdio.h>
#include <stdlib.h>
#include "soundpipe.h"

typedef struct {
   sp_ftbl *ft;
   sp_osc *osc;
   sp_clip *clp;
} udata;

void write_clip(sp_data *sp, void *ud) {
    udata *udp = ud;
    SPFLOAT out, osc;

    //if pos is 0 - 88200, no clip
    if(sp->pos < 88200) {
        sp_osc_compute(sp, udp->osc, NULL, &osc);
        sp->out[0] = osc;
        
    }
    //if pos is 88200 - 44100 *3, clip method 0
    if(sp->pos >= 88200 && sp->pos < (44100 * 3)) {
        udp->clp->meth = 0;
        sp_osc_compute(sp, udp->osc, NULL, &osc);
        sp_clip_compute(sp, udp->clp, &osc, &out);
        sp->out[0] = out;
    }
    //if pos is 44100 * 3 - 44100 * 4, clip method 1
    if(sp->pos >= (44100 * 3) && sp->pos < (44100 * 4)) {
        udp->clp->meth = 1;
        udp->clp->lim = 0.2;
        sp_osc_compute(sp, udp->osc, NULL, &osc);
        sp_clip_compute(sp, udp->clp, &osc, &out);
        sp->out[0] = out;
    }
    //if pos is 44100 * 4 - 44100 * 5, clip method 2
    if(sp->pos >= (44100 * 4) && sp->pos < (44100 * 5)) {
        udp->clp->meth = 2;
        udp->clp->lim = 0.2;
        sp_osc_compute(sp, udp->osc, NULL, &osc);
        sp_clip_compute(sp, udp->clp, &osc, &out);
        sp->out[0] = out * 0.5;
    }
}

int main() {
    udata ud;
    sp_data *sp;
    sp_create(&sp);
    sp_clip_create(&ud.clp);
    sp_osc_create(&ud.osc);
    sp_ftbl_create(sp, &ud.ft, 4096);

    sp_gen_line(sp, ud.ft, "1 4096 -1");
    sp_osc_init(sp, ud.osc, ud.ft);
    ud.osc->freq = sp_midi2cps(48);
    sp_clip_init(sp, ud.clp, 0, 0.5);
    sp->len = 44100 * 5;
    sp_process(sp, &ud, write_clip);

    sp_osc_destroy(&ud.osc);
    sp_clip_destroy(&ud.clp);
    sp_ftbl_destroy(&ud.ft);

    sp_destroy(&sp);
    return 0;
}
