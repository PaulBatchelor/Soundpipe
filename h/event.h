#ifndef __SOUNDPIPE_H__
#include "soundpipe.h"
#define __SOUNDPIPE_H__
#endif

enum{
SPEVT_FREE,
SPEVT_QUEUED,
SPEVT_ON,
SPEVT_OFF,
SPEVT_ERROR
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

}sp_evtstack; 

int sp_event_init(sp_event **evt);
int sp_event_destroy(sp_event **evt);
int sp_event_create(sp_event *evt, 
        sp_frame cpos, sp_frame start, sp_frame dur,
        void(*init_cb)(void *),
        void(*evton_cb)(void *),
        void(*evtoff_cb)(void *),
        void *ud); 
int sp_event_clear(sp_event *evt);
int sp_event_update(sp_event *evt, sp_frame pos);
int sp_event_exec(sp_event *evt);

/* event stack functions */

int sp_evtstack_create(sp_evtstack **es, int nvoices);
int sp_evtstack_init(sp_evtstack *es);
int sp_evtstack_destroy(sp_evtstack **es);

int sp_evtstack_add(sp_evtstack *es, 
        sp_frame cpos, sp_frame start, sp_frame dur,
        void(*init_cb)(void *),
        void(*evton_cb)(void *),
        void(*evtoff_cb)(void *),
        void *ud); 

int sp_evtstack_nextfree(sp_evtstack *es, int *id);

int sp_evtstack_update(sp_evtstack *evt, sp_frame pos);
int sp_evtstack_exec(sp_evtstack *evt);
