#include "soundpipe.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

#define NOSC 5

typedef struct {
    sp_talkbox *talkbox;
    sp_blsaw *saw[NOSC];
    sp_diskin *diskin;
} UserData;

static int chord[] = {48, 51, 55, 60, 70};

static SPFLOAT process(sp_data *sp, void *udata) {
    UserData *ud = udata;
    SPFLOAT tmp;
    int i;
    SPFLOAT src = 0;
    SPFLOAT exc = 0;
    SPFLOAT talkbox = 0;

    exc = 0;
    for(i = 0; i < NOSC; i++) {
		sp_blsaw_compute(sp, ud->saw[i], NULL, &tmp);
		exc += tmp;
    }
    sp_diskin_compute(sp, ud->diskin, NULL, &src);
    src *= 0.5;
    sp_talkbox_compute(sp, ud->talkbox, &src, &exc, &talkbox);
    return talkbox;
}

int t_talkbox(sp_test *tst, sp_data *sp, const char *hash) 
{
    uint32_t n;
    UserData ud;
    int fail = 0;
    int i;
    SPFLOAT tmp;

    /* allocate / initialize modules here */
    sp_srand(sp, 1234567);

    sp_diskin_create(&ud.diskin);
	sp_talkbox_create(&ud.talkbox);
	sp_talkbox_init(sp, ud.talkbox);
	ud.talkbox->quality = 0.2;

	for(i = 0; i < NOSC; i++) {
		sp_blsaw_create(&ud.saw[i]);
		sp_blsaw_init(sp, ud.saw[i]);
		*ud.saw[i]->freq = sp_midi2cps(chord[i]);
		*ud.saw[i]->amp = 0.1;
    }

    sp_diskin_init(sp, ud.diskin, SAMPDIR "oneart.wav");


    for(n = 0; n < tst->size; n++) {
    	tmp = process(sp, &ud);
        sp_test_add_sample(tst, tmp);
    }

    fail = sp_test_verify(tst, hash);

    sp_talkbox_destroy(&ud.talkbox);
    for(i = 0; i < NOSC; i ++) {
		sp_blsaw_destroy(&ud.saw[i]);
    }
    sp_diskin_destroy(&ud.diskin);

    if(fail) return SP_NOT_OK;
    else return SP_OK;
}
