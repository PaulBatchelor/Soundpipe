#include <soundpipe.h>
#include "test.c"

typedef struct {
   mydsp *dsp;
   SPFLOAT *p[2];
   UIGlue UI;
   SPFLOAT *amp, *freq;
   int pos;
   int size;
} UserData;


void layout_dummy (void* ui_interface, const char* label)
{

}

void declare_dummy (void* ui_interface, FAUSTFLOAT* zone, const char* key, const char* value)
{

}

void close_dummy (void* ui_interface)
{

}

void add_param(void* ui_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
{
    UserData *ud = ui_interface;
    if(ud->pos < 0) {
        return;
    }
    SPFLOAT **p = ud->p;
    p[ud->pos--] = zone;
}


void process(sp_data *sp, void *udata)
{
    UserData *ud = udata;
    SPFLOAT out;
    SPFLOAT *outp = &out;
    computemydsp(ud->dsp, 1, NULL, &outp);
    sp->out[0] = out;
}

int main()
{
    sp_data *sp;
    UserData ud;

    sp_create(&sp);
    ud.dsp = newmydsp();
    ud.UI.uiInterface = &ud;
    ud.size = 2;
    ud.pos = --ud.size;
    initmydsp(ud.dsp, sp->sr);
    ud.UI.openVerticalBox = layout_dummy;
    ud.UI.declare = declare_dummy;
    ud.UI.closeBox = close_dummy;
    ud.UI.addHorizontalSlider = add_param;
    buildUserInterfacemydsp(ud.dsp, &ud.UI);
    ud.freq = ud.p[1];
    ud.amp = ud.p[0];

    *ud.freq = 440;
    sp_process(sp, &ud, process);
    deletemydsp(ud.dsp);
    sp_destroy(&sp);
}
