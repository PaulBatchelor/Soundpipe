#include "soundpipe.h"

typedef struct {

sp_diskin *file;
sp_jcrev *dsp;

} UserData;

void process(sp_data *sp, void *udata)
{
    UserData *ud = udata;
    SPFLOAT in = 0, out = 0;

    sp_diskin_compute(sp, ud->file, NULL, &in);
    sp_jcrev_compute(sp, ud->dsp, &in, &out);

    sp->out[0] = out;
}

int main()
{
    sp_data *sp;
    UserData ud;

    sp_create(&sp);
    sp_jcrev_create(&ud.dsp);
    sp_diskin_create(&ud.file);

    sp_jcrev_init(sp, ud.dsp);
    sp_diskin_init(sp, ud.file, "oneart.wav");

    sp_process(sp, &ud, process);

    sp_jcrev_destroy(&ud.dsp);
    sp_diskin_destroy(&ud.file);
    sp_destroy(&sp);
}
