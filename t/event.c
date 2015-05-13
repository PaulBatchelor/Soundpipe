#include <stdio.h>
#include <stdbool.h>
#include "tap.h"
#include "event.h"

typedef struct {
int init_val;
int noton_val;
int notoff_val;
}Test_Data;

void init_cb(void *ud){
    Test_Data *t = ud;
    t->init_val = 1; 
}

void noton_cb(void *ud){
    Test_Data *t = ud;
    if(t->noton_val > 0){
        t->noton_val++;
    }
    t->noton_val = 2; 
}

void notoff_cb(void *ud){
    Test_Data *t = ud;
    t->notoff_val = 3; 
}


int main( int argc, char** argv ) {
    plan( 8 );
    sp_event *e; 
    int status;
    Test_Data td;
    Test_Data *tp = &td;
    td.init_val = -1;
    td.noton_val = -1;
    td.notoff_val = -1;

    status = sp_event_init(&e);
    ok(status, "Initialize event");

    if(!status){
        printf("Cannot go futher until event has been initalized. Breaking...\n");
        return 1;    
    };

    status = sp_event_create(e, 1, 5, 
           init_cb, noton_cb, notoff_cb, 
           &tp);
    ok(status, "create event");

    if(!status){
        printf("Tests after this one rely on sp_event_create "
                "to pass in order to continue. Breaking...\n");
        return 1;    
    };

    
    sp_event_update(e, 0);
    ok(e->mode == SPEVT_QUEUED, "QUEUED mode enabled");
    sp_event_exec(e);
    ok(td.init_val == 1, "Init callback working");
    sp_event_update(e, 1);
    ok(e->mode == SPEVT_NOTON, "NOTON mode enabled");
    sp_event_exec(e);
    ok(td.noton_val == 2, "note on callback working");
    sp_event_update(e, 2);
    sp_event_exec(e);
    ok(td.noton_val == 3, "note on callback updating");
    sp_event_update(e, 5);
    ok(e->mode == SPEVT_NOTOFF, "NOTOFF mode enabled");
    sp_event_exec(e);
    ok(td.notoff_val == 3, "note off callback updating");
    sp_event_update(e, 6);
    sp_event_exec(e);
    ok(e->mode == SPEVT_FREE && td.notoff_val == 3, "Event is freed at the right time");
    sp_event_destroy(&e);
    return 0;
}
