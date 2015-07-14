#include "soundpipe.h"

typedef struct {
    sp_comb *comb;
    sp_tenv *env;
    sp_noise *nz;
} UserData;

void process(sp_data *sp, void *udata) {
    UserData *ud = udata;
    SPFLOAT tick = 0, env = 0, noise = 0, comb = 0;

    tick = (sp->pos == 0) ? 1 : 0;
    sp_tenv_compute(sp, ud->env, &tick, &env);
    sp_noise_compute(sp, ud->nz, NULL, &noise);
    noise *= env * 0.5;
    sp_comb_compute(sp, ud->comb, &noise, &comb);

    sp->out[0] = comb;
}


int main()
{
    UserData ud;
    sp_data *sp;
    sp_create(&sp);
   
    sp_comb_create(&ud.comb);
    sp_tenv_create(&ud.env);
    sp_noise_create(&ud.nz);

    sp_comb_init(sp, ud.comb, 0.01);
    sp_tenv_init(sp, ud.env, 0.001, 0.00, 0.1);
    sp_noise_init(sp, ud.nz);

    sp->len = 44100 * 5;
    sp_process(sp, &ud, process);

    sp_noise_destroy(&ud.nz);
    sp_tenv_destroy(&ud.env);
    sp_comb_destroy(&ud.comb);

    sp_destroy(&sp);
    return 0;
}
