/*
 * This is a dummy example.
 * Please implement a small and simple working example of your module, and then
 * remove this header.
 * Don't be clever.
 * Bonus points for musicality.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "soundpipe.h"

typedef struct {
    sp_granule *granule;
    sp_ftbl *env;
    sp_ftbl *wav;
} UserData;

void process(sp_data *sp, void *udata) {
    UserData *ud = udata;
    SPFLOAT granule = 0;
    sp_granule_compute(sp, ud->granule, NULL, &granule);
    sp->out[0] = granule;
}

int main() {
    UserData ud;
    sp_data *sp;
    SPFLOAT amp;
    SPFLOAT ivoice;
    SPFLOAT iratio;
    SPFLOAT imode;
    SPFLOAT ithd;
    SPFLOAT ipshift;
    SPFLOAT igskip;
    SPFLOAT igskip_os;
    SPFLOAT ilength;
    SPFLOAT kgap;
    SPFLOAT igap_os;
    SPFLOAT kgsize;
    SPFLOAT igsize_os;
    SPFLOAT iatt;
    SPFLOAT idec;
    SPFLOAT iseed;
    SPFLOAT ipitch1;
    SPFLOAT ipitch2;
    SPFLOAT ipitch3;
    SPFLOAT ipitch4;


    ivoice = 64;
    iratio = 0.5;
    imode = 0;
    ithd = 0;
    ipshift = 4;
    igskip = 0;
    igskip_os = 0.005;
    ilength = 5;
    kgap = 0.01;
    igap_os = 50;
    kgsize = 0.02;
    igsize_os = 50;
    iatt = 30;
    idec = 30;
    iseed = 0.39;
    ipitch1 = 1;
    ipitch2 = 1.42;
    ipitch3 = 0.29;
    ipitch4 = 2;

    sp_create(&sp);
    sp_srand(sp, 1234567);

    sp_granule_create(&ud.granule);
    sp_ftbl_create(sp, &ud.env, 2048);
    sp_gen_composite(sp, ud.env, "0.5 1 0 0.5");

    sp_ftbl_loadfile(sp, &ud.wav, "oneart.wav");
    sp_granule_init(sp, ud.granule,
                        ivoice,
                        iratio,
                        imode,
                        ithd,
                        ud.wav,
                        ipshift,
                        igskip,
                        igskip_os,
                        ilength,
                        igap_os,
                        igsize_os,
                        iatt,
                        idec,
                        iseed,
                        ipitch1,
                        ipitch2,
                        ipitch3,
                        ipitch4,
                        ud.env);

    ud.granule->xamp = 0.1;
    sp->len = 44100 * 5;
    sp_process(sp, &ud, process);

    sp_granule_destroy(&ud.granule);
    sp_ftbl_destroy(&ud.env);
    sp_ftbl_destroy(&ud.wav);

    sp_destroy(&sp);
    return 0;
}
