#include <stdlib.h>
#include "event.h"

int sp_create_evt_stack(sp_data *sp, int nvoices){
    return 1;
}
int sp_destroy_evt_stack(sp_data *sp, int nvoices){
    return 1;
}
int sp_event_update(sp_event *evt, sp_frame pos){
    if(evt->mode == SPEVT_FREE){
        return SP_OK;
    }else if(pos < evt->start){
        evt->mode = SPEVT_QUEUED;
    }else if(pos >= evt->start && pos < evt->end - 1){
        evt->mode = SPEVT_NOTON;
    }else if(pos == evt->end - 1 && evt->mode == SPEVT_NOTON){
        evt->mode = SPEVT_NOTOFF;
    }else if(pos == evt->end && evt->mode == SPEVT_NOTOFF){
        evt->mode = SPEVT_FREE;
    }else {
        return SP_NOT_OK;
    }
}
int sp_event_create(sp_event *evt, 
        sp_frame start, sp_frame dur,
        void(*init_cb)(void *),
        void(*noton_cb)(void *),
        void(*notoff_cb)(void *),
        void *ud){ 

    if(evt->mode != SPEVT_FREE) {
            fprintf(stderr, "Error: event mode is not set to SPEVT_FREE. Properly "
                "remove current event before proceeding.\n");
        return SP_NOT_OK;
    }

    if(dur < 1){
        fprintf(stderr, "Error: invalid duration %d.", dur);
        return SP_NOT_OK;
    }

    evt->start = start;
    evt->end = start + dur;
    evt->init_cb = init_cb; 
    evt->noton_cb = noton_cb; 
    evt->notoff_cb = notoff_cb; 
    evt->ud = ud;

    evt->mode = SPEVT_QUEUED;
    evt->init_cb(evt->ud);
    return SP_OK;
}
int sp_event_exec(sp_event *evt) {
    switch(evt->mode){
    case SPEVT_FREE:
        return SP_OK;
        break;
    case SPEVT_NOTON:
        evt->noton_cb(evt->ud);
        return SP_OK;
        break;
    case SPEVT_NOTOFF:
        evt->notoff_cb(evt->ud);
        return SP_OK;
    case SPEVT_QUEUED:
        return SP_OK;
    default:
        return SP_NOT_OK;
    }
}
int sp_event_init(sp_event **evt){ *evt = malloc(sizeof(sp_event));
    sp_event *ep = *evt;
    ep->mode = SPEVT_FREE;
    return SP_OK;
}
int sp_event_destroy(sp_event **evt){

    return SP_NOT_OK;
}
