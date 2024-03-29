#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "soundpipe.h"

typedef struct {
    sp_osc *osc1;
    sp_osc *osc2;
    sp_ftbl *ft;
    sp_metro *met;
    sp_tenv *tenv1;
    sp_tenv *tenv2;
    sp_tdiv *tdiv;
} UserData;

static void write_tdiv(sp_data *sp, void *udata) {
    UserData *ud = udata;
    SPFLOAT trig = 0;
    SPFLOAT div  = 0;
    SPFLOAT env1 = 0;
    SPFLOAT env2 = 0;
    SPFLOAT osc1 = 0;
    SPFLOAT osc2 = 0;
    sp_metro_compute(sp, ud->met, NULL, &trig);
    sp_tdiv_compute(sp, ud->tdiv, &trig, &div);
    sp_osc_compute(sp, ud->osc1, NULL, &osc1);
    sp_osc_compute(sp, ud->osc2, NULL, &osc2);

    sp_tenv_compute(sp, ud->tenv1, &trig, &env1);
    sp_tenv_compute(sp, ud->tenv2, &div, &env2);

    sp->out[0] = (osc1 * env1) + (osc2 * env2);
}

int main() {
    UserData ud;
    sp_data *sp;
    sp_create(&sp);
    sp_srand(sp, 123456);

    sp_tenv_create(&ud.tenv1);
    sp_tenv_create(&ud.tenv2);
    sp_metro_create(&ud.met);
    sp_ftbl_create(sp, &ud.ft, 2048);
    sp_osc_create(&ud.osc1);
    sp_osc_create(&ud.osc2);
    sp_tdiv_create(&ud.tdiv);

    sp_tenv_init(sp, ud.tenv1);
    ud.tenv1->atk = 0.03;
    ud.tenv1->hold = 0.01;
    ud.tenv1->rel = 0.1;

    sp_tenv_init(sp, ud.tenv2);
    ud.tenv2->atk = 0.03;
    ud.tenv2->hold = 0.01;
    ud.tenv2->rel = 0.1;

    sp_metro_init(sp, ud.met);
    ud.met->freq = 3;
    sp_gen_sine(sp, ud.ft);
    sp_osc_init(sp, ud.osc1, ud.ft, 0);
    ud.osc1->freq = 400;
    sp_osc_init(sp, ud.osc2, ud.ft, 0);
    ud.osc2->freq = 800;

    sp_tdiv_init(sp, ud.tdiv);
    ud.tdiv->num = 3;

    sp->len = 44100 * 5;
    sp_process(sp, &ud, write_tdiv);

    sp_tenv_destroy(&ud.tenv1);
    sp_tenv_destroy(&ud.tenv2);
    sp_metro_destroy(&ud.met);
    sp_ftbl_destroy(&ud.ft);
    sp_osc_destroy(&ud.osc1);
    sp_osc_destroy(&ud.osc2);
    sp_tdiv_destroy(&ud.tdiv);
    sp_destroy(&sp);
    return 0;
}
