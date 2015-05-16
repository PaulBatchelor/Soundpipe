#ifndef __SOUNDPIPE_H__
#include "soundpipe.h"
#define __SOUNDPIPE_H__
#endif

enum{
SPEVT_FREE,
SPEVT_QUEUED,
SPEVT_ON,
SPEVT_OFF,
SPEVT_ERROR,
SPEVT_ONESAMP
};

enum{
SPEVSTK_SEARCH = -2,
SPEVSTK_NOFREE
};

typedef struct {
    int mode;
    sp_frame start;
    sp_frame end;
    void (*init_cb)(void *);
    void (*evton_cb)(void *);
    void (*evtoff_cb)(void *);
    void **ud;
}sp_event; 

typedef struct {
    sp_event *evt;
    int nevents;
    int nxtfree;
    int curfree;
    int lstfree;
}sp_evtstack; 

int sp_event_create(sp_event **evt, int nevents);
int sp_event_inti(sp_event *evt);
int sp_event_destroy(sp_event **evt);
/* poorly named function because create implies memory mgt. change. */
int sp_event_insert(sp_event *evt, 
        sp_frame cpos, sp_frame start, sp_frame dur,
        void(*init_cb)(void *),
        void(*evton_cb)(void *),
        void(*evtoff_cb)(void *),
        void *ud); 
int sp_event_clear(sp_event *evt);
int sp_event_update(sp_event *evt, sp_frame pos);
int sp_event_exec(sp_event *evt);

/* event stack functions */

int sp_evtstack_create(sp_evtstack **es, int nevents);
int sp_evtstack_init(sp_evtstack *es);
int sp_evtstack_destroy(sp_evtstack **es);

int sp_evtstack_add(sp_evtstack *es, 
        sp_frame cpos, sp_frame start, sp_frame dur,
        void(*init_cb)(void *),
        void(*evton_cb)(void *),
        void(*evtoff_cb)(void *),
        void *ud); 

int sp_evtstack_nextfree(sp_evtstack *es, int *id);

int sp_evtstack_update(sp_evtstack *es, sp_frame pos);
int sp_evtstack_exec(sp_evtstack *es);
