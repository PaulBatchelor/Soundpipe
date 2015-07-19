#include "soundpipe.h"

typedef struct{
    sp_osc *osc;
    sp_ftbl *ft;
    sp_metro *mt;
    sp_tenv *te;
    sp_rpt *rpt;
    sp_maygate *mg;
}UserData;

void compute(sp_data *sp, void *user_data){
    UserData *ud = user_data;
    SPFLOAT met, osc, env, rpt, maygate, trig, dry;
    sp_metro_compute(sp, ud->mt, NULL, &met);
    sp_tenv_compute(sp, ud->te, &met, &env);
    sp_osc_compute(sp, ud->osc, NULL, &osc);
    dry = osc * env;
    sp_maygate_compute(sp, ud->mg, &met, &maygate);
    trig = met * maygate;
    sp_rpt_compute(sp, ud->rpt, &trig, &dry, &rpt);
    sp->out[0] = rpt;
}

int main(){
    sp_data *sp;
    UserData ud;
    sp_create(&sp);
    int tempo = 120;
    sp_rpt_create(&ud.rpt);
    sp_maygate_create(&ud.mg);
    sp_osc_create(&ud.osc);
    sp_ftbl_create(sp, &ud.ft, 4096);
    sp_metro_create(&ud.mt);
    sp_tenv_create(&ud.te);

   
    sp_maygate_init(sp, ud.mg, 0.5);
    sp_gen_sine(sp, ud.ft);
    sp_osc_init(sp, ud.osc, ud.ft);
    sp_metro_init(sp, ud.mt, tempo / 60.0);
    sp_rpt_init(sp, ud.rpt, 1.0);
    ud.rpt->bpm = tempo;
    ud.rpt->div = 8;
    ud.rpt->rep = 4;
    sp_tenv_init(sp, ud.te, 0.001, 0.1, 0.1); 
    sp_process(sp, &ud, compute);

    sp_tenv_destroy(&ud.te);
    sp_metro_destroy(&ud.mt);
    sp_ftbl_destroy(&ud.ft);
    sp_osc_destroy(&ud.osc);
    sp_rpt_destroy(&ud.rpt);

    sp_destroy(&sp);
    return 0;
}
