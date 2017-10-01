#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "soundpipe.h"

#define NOSC 5

typedef struct {
    sp_talkbox *talkbox;
    sp_blsaw *saw[NOSC];
    sp_diskin *diskin;
} UserData;

static int chord[] = {48, 51, 55, 60, 70};

void process(sp_data *sp, void *udata) {
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
    sp_out(sp, 0, talkbox);
}

int main() {
    UserData ud;
    sp_data *sp;
    int i;
    sp_create(&sp);
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

    sp_diskin_init(sp, ud.diskin, "oneart.wav");

    sp->len = 44100 * 8;
    sp_process(sp, &ud, process);

    sp_talkbox_destroy(&ud.talkbox);
    for(i = 0; i < NOSC; i ++) {
		sp_blsaw_destroy(&ud.saw[i]);
    }
    sp_diskin_destroy(&ud.diskin);

    sp_destroy(&sp);
    return 0;
}
