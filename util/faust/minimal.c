#include <math.h>
#include "CUI.h"

#define max(a,b) ((a < b) ? b : a)
#define min(a,b) ((a < b) ? a : b)

<<includeIntrinsic>>

<<includeclass>>

/* -- layout groups */

static void openTabBox (void* ui_interface, const char* label)
{

}

static void openHorizontalBoxFun (void* ui_interface, const char* label)
{

}
static void openVerticalBoxFun (void* ui_interface, const char* label)
{

}

static void closeBoxFun (void* ui_interface)
{

}

/* -- active widgets */

static void addButton (void* ui_interface, const char* label, FAUSTFLOAT* zone)
{

}

static void addCheckButton (void* ui_interface, const char* label, FAUSTFLOAT* zone)
{

}

static void addVerticalSlider (void* ui_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
{

}

static void addHorizontalSliderFun (void* ui_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
{

}

static void addNumEntryFun (void* ui_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
{

}

/* -- passive display widgets */

static void addHorizontalBargraphFun (void* ui_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
{

}

static void addVerticalBargraphFun (void* ui_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
{

}

static void declareFun (void* ui_interface, FAUSTFLOAT* zone, const char* key, const char* value)
{

}

/* put this struct in a header called mydsp.h */

typedef struct {
    void *ud;
} sp_mydsp;

int sp_mydsp_create(sp_mydsp **p);
int sp_mydsp_destroy(sp_mydsp **p);
int sp_mydsp_init(sp_data *sp, sp_mydsp *p);
int sp_mydsp_compute(sp_data *sp, sp_mydsp *p, SPFLOAT *in, SPFLOAT *out);

int sp_mydsp_create(sp_mydsp **p)
{
    *p = malloc(sizeof(sp_mydsp));
    return SP_OK;
}

int sp_mydsp_destroy(sp_mydsp **p)
{
    sp_mydsp *pp = *p;
    mydsp *dsp = pp->ud;
    deletemydsp(dsp);
    free(*p);
    return SP_OK;
}

int sp_mydsp_init(sp_data *sp, sp_mydsp *p)
{
    mydsp *dsp = newmydsp();
    UIGlue UI;

    UI.openTabBox = openTabBox;
    UI.openHorizontalBox = openHorizontalBox;
    UI.openVerticalBox = openVerticalBox;
    UI.closeBox = closeBox;
    UI.addButton = addButton;
    UI.addCheckButton = addCheckButton;
    UI.addVerticalSlider = addVerticalSlider;
    UI.addHorizontalSlider= addHorizontalSlider;
    UI.addNumEntry = addNumEntry;
    UI.addHorizontalBargraph= addHorizontalBargraph;
    UI.declare = declare;

    initmydsp(dsp, sp->sr);
    p->ud = dsp;
    return SP_OK;
}

int sp_mydsp_compute(sp_data *sp, sp_mydsp *p, SPFLOAT *in, SPFLOAT *out)
{

    mydsp *dsp = p->ud;
    SPFLOAT out1 = 0, out2 = 0, out3 = 0, out4 = 0;
    SPFLOAT *faust_out[] = {&out1, &out2, &out3, &out4};
    computemydsp(dsp, 1, &in, faust_out);

    *out = out1;
    return SP_OK;
}
