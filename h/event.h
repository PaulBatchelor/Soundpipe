#ifndef __SOUNDPIPE_H__
#include "soundpipe.h"
#define __SOUNDPIPE_H__
#endif

enum{
SPEVT_FREE,
SPEVT_QUEUED,
SPEVT_NOTON,
SPEVT_NOTOFF,
SPEVT_ERROR
};

typedef struct {
    int mode;
    sp_frame start;
    sp_frame end;
    void (*init_cb)(void *);
    void (*noton_cb)(void *);
    void (*notoff_cb)(void *);
    void **ud;
}sp_event; 

typedef struct {

}sp_evt_stack; 

int sp_create_evt_stack(sp_data *sp, int nvoices);
int sp_destroy_evt_stack(sp_data *sp, int nvoices);
int sp_event_init(sp_event **evt);
int sp_event_destroy(sp_event **evt);
int sp_event_create(sp_event *evt, 
        sp_frame cpos, sp_frame start, sp_frame dur,
        void(*init_cb)(void *),
        void(*noton_cb)(void *),
        void(*notoff_cb)(void *),
        void *ud); 
int sp_event_clear(sp_event *evt);
int sp_event_update(sp_event *evt, sp_frame pos);
int sp_event_exec(sp_event *evt);
