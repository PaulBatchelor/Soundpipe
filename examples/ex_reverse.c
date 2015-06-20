#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "soundpipe.h"

typedef struct {
    sp_osc *osc;
    sp_ftbl *ft; 
    sp_tenv *tenv;
    sp_reverse *rv;
} udata;

void write_osc(sp_data *data, void *ud) {
    udata *udp = ud;
    SPFLOAT env = 0;
    SPFLOAT osc = 0;
    SPFLOAT rv = 0;
    SPFLOAT dry = 0;
    SPFLOAT trig;
    if(data->pos == 0){
        trig = 1.0;
    }else{
        trig = 0.0;
    }
    sp_tenv_compute(data, udp->tenv, &trig, &env);
    sp_osc_compute(data, udp->osc, NULL, &osc);
    dry = osc * env;
    sp_reverse_compute(data, udp->rv, &dry, &rv);
    data->out = dry + rv;
}

int main() {
    srand(time(NULL));
    udata ud;
    uint32_t bufsize;
    sp_data *sp;
    sp_create(&sp);
    
    sp_reverse_create(sp, &ud.rv);
    sp_tenv_create(&ud.tenv);
    sp_ftbl_create(sp, &ud.ft, 2048);
    sp_osc_create(&ud.osc);

    sp_reverse_init(sp, ud.rv, 1.0);
    sp_tenv_init(sp, ud.tenv, 0.03, 0.01, 0.3);
    sp_gen_sine(ud.ft);
    sp_osc_init(sp, ud.osc, ud.ft);
    ud.osc->freq = 1000;
    ud.osc->amp = 0.5;
    sp_gen_sine(ud.ft);
    sp->len = 44100 * 5;
    sp_process(sp, &ud, write_osc);

    sp_reverse_destroy(&ud.rv);
    sp_tenv_destroy(&ud.tenv);
    sp_ftbl_destroy(&ud.ft);
    sp_osc_destroy(&ud.osc);
    sp_destroy(&sp);
    return 0;
}
