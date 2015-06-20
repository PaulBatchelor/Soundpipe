#include <stdio.h>
#include <stdbool.h>
#include "tap.h"
#include "base.h"
#include "event.h"

typedef struct {
int init_val;
int evton_val;
int evtoff_val;
int v1, v2, v3; 
long v4, v5, v6;
int id;
}Test_Data;

void print_testdata(Test_Data *td, int nvals){
    int i;
    for(i = 0; i < nvals; i++){
        printf("event %d ID is %d\n", i, td[i]);
    }
}

void init_cb(void *ud){
    Test_Data *t = (Test_Data *) ud;
    t->init_val = 1; 
}

void evton_cb(void *ud){
    Test_Data *t = ud;
    if(t->evton_val > 0){
        t->evton_val++;
    }else{
        t->evton_val = 2;
    }
}

void evton_cb2(void *ud){
    Test_Data *t = ud;
    t->evton_val = 2;
}



void evtoff_cb(void *ud){
    Test_Data *t = ud;
    t->evtoff_val = 3; 
}

void init_test_vars(Test_Data *tp){
    tp->init_val = -1;
    tp->evton_val = -1;
    tp->evtoff_val = -1;
    tp->v1 = -1;
    tp->v2 = -1;
    tp->v3 = -1;
    tp->id = -1;
}

int main( int argc, char** argv ) {
    plan( 27 );
    sp_event *e; 
    int status, i, id;

    Test_Data td;
    Test_Data td_es[3];
    Test_Data *tp_es = td_es;
    Test_Data *tp = &td;
    init_test_vars(tp);
    status = sp_event_create(&e, 1);
    sp_event_init(e);
    ok(status, "Initialize event");

    if(!status){
        printf("Cannot go futher until event has been initalized. Breaking...\n");
        return 1;    
    };
    status = sp_event_insert(e, 0, 1, 5, 
           init_cb, evton_cb, evtoff_cb, 
           tp);
    ok(status, "insert event");

    if(!status){
        printf("Tests after this one rely on sp_event_insert "
                "to pass in order to continue. Breaking...\n");
        return 1;    
    };

    printf("\n** Testing normal use of event functions... **\n\n");
    sp_event_update(e, 0);
    ok(e->mode == SPEVT_QUEUED, "QUEUED mode enabled");
    sp_event_exec(e);
    ok(td.init_val == 1, "Init callback working");

    sp_event_update(e, 1);
    ok(e->mode == SPEVT_ON, "ON mode enabled");
    sp_event_exec(e);
    ok(td.evton_val == 2, "note on callback working");

    sp_event_update(e, 2);
    sp_event_exec(e);
    ok(td.evton_val == 3, "note on callback updating");

    sp_event_update(e, 5);
    ok(e->mode == SPEVT_OFF, "OFF mode enabled");
    sp_event_exec(e);
    ok(td.evtoff_val == 3, "note off callback updating");

    sp_event_update(e, 6);
    sp_event_exec(e);
    ok(e->mode == SPEVT_FREE && td.evtoff_val == 3, "Event is freed at the right time");
   
    printf("\n** Adding event when its time has passed... **\n\n");
    sp_event_insert(e, 2, 1, 5, init_cb, evton_cb, evtoff_cb, tp);

    /* Error testing! */

    init_test_vars(tp);
    status = sp_event_update(e, 2);
    ok(status == SP_NOT_OK, "Making sure event returns SP_NOT_OK");
    sp_event_exec(e);
    ok(tp->init_val == -1, "Making sure init_cb isn't called."); 

    status = sp_event_update(e, 1);
    ok(status == SP_NOT_OK, 
            "Making sure this otherwise note on event returns SP_NOT_OK");
    sp_event_exec(e);
    ok(tp->evton_val == -1, "Making sure evton_cb isn't called."); 
    
    status = sp_event_update(e, 5);
    ok(status == SP_NOT_OK, 
            "Making sure this otherwise note off event returns SP_NOT_OK");
    sp_event_exec(e);
    ok(tp->evtoff_val == -1, "Making sure evtoff_cb isn't called."); 
    
    sp_event_destroy(&e);
    
    printf("\n** Misc error handling and exceptions... **\n\n");
    
    sp_event_create(&e, 1);
    sp_event_init(e);
    sp_event_insert(e, 0, 0, 1, init_cb, evton_cb, evtoff_cb, tp);
    sp_event_update(e, 0);
    sp_event_exec(e);
    ok(e->mode == SPEVT_FREE, "1 sample duration events are freed at the right time");
    sp_event_destroy(&e);
    
    sp_event_create(&e, 1);
    sp_event_init(e);
    sp_event_insert(e, 0, 4, 1, init_cb, evton_cb, evtoff_cb, tp);
    sp_event_update(e, 0);
    sp_event_exec(e);
    td.v1 = e->mode;

    for(i = 1; i <= 5; i++){
        sp_event_update(e, i);
        sp_event_exec(e);
    }
    td.v2 = e->mode;
    ok(td.v1 == SPEVT_QUEUED && td.v2== SPEVT_FREE, 
            "1 sample duration events are queued + freed at the right time");
    sp_event_destroy(&e);
    
    sp_event_create(&e, 1);
    sp_event_init(e);

    sp_event_insert(e, 0, 1, 5, init_cb, evton_cb, evtoff_cb, tp);
    status = sp_event_insert(e, 0, 2, 5, init_cb, evton_cb, evtoff_cb, tp);
    ok(status == SP_NOT_OK, 
            "Making sure event cannot be overwritten.");
    sp_event_clear(e);
    status = sp_event_insert(e, 0, 2, 5, init_cb, evton_cb, evtoff_cb, tp);
    ok(status == SP_OK, 
            "Making sure event can be overriden when it is explicitely cleared.");

    sp_event_destroy(&e);

    /* Event Stack tests go here */
  
    printf("\n** Event stack tests... **\n\n");

    sp_evtstack *es;

    status = sp_evtstack_create(&es, 3);

    if(!status){
        printf("The following tests rely on sp_evtstack_insert "
                "to pass in order to continue. Breaking...\n");
        return 1;    
    };
   
    sp_evtstack_init(es, init_cb, evton_cb, evtoff_cb, td_es, sizeof(Test_Data));

    sp_evtstack_add(es, 0, 0, 5, &id);
    td.v1 = es->lstfree; 
    sp_evtstack_add(es, 0, 0, 5, &id);
    td.v2 = es->lstfree; 
    sp_evtstack_add(es, 0, 0, 5, &id);
    td.v3 = es->lstfree; 
    
    ok(td.v1 == 0 && td.v2 == 1 && td.v3 == 2, "Event stack adds in correct order.");

    sp_evtstack_destroy(&es);

    status = sp_evtstack_create(&es, 3);

    sp_evtstack_init(es, init_cb, evton_cb, evtoff_cb, td_es, sizeof(Test_Data));

    sp_evtstack_add(es, 0, 0, 5, &id);
    td.v1 = es->lstfree; 
    sp_evtstack_add(es, 0, 0, 5, &id);
    td.v2 = es->lstfree; 
    sp_evtstack_add(es, 0, 0, 5, &id);
    td.v3 = es->lstfree; 
    
    status = sp_evtstack_add(es, 0, 0, 5, &id);
    
    sp_evtstack_destroy(&es);

    ok(td.v3 == 2 && status == SP_NOT_OK, "Event overflow handling.");

    status = sp_evtstack_create(&es, 3);
    sp_evtstack_init(es, init_cb, evton_cb, evtoff_cb, td_es, sizeof(Test_Data));

    sp_evtstack_add(es, 0, 0, 10, &id);
    sp_evtstack_add(es, 0, 0, 5, &id);
    sp_evtstack_add(es, 0, 0, 10, &id);

    for(i = 0; i <= 5; i++){
        sp_evtstack_update(es, i);
    }

    sp_evtstack_add(es, 5, 7, 5, &id);
    td.v1 = es->lstfree; 

    ok(td.v1 == 1 && status == SP_OK, "Voices being freed properly.");

    sp_evtstack_destroy(&es);

    sp_evtstack_create(&es, 3);
    sp_evtstack_init(es, init_cb, evton_cb2, evtoff_cb, td_es, sizeof(Test_Data));
    for(i = 0; i < 3; i++) init_test_vars(&td_es[i]);
    sp_evtstack_add(es, 0, 0, 4, &id);

    for(i = 0; i <= 5; i++){
        sp_evtstack_update(es, i);
        sp_evtstack_exec(es);
    }
    ok(td_es[es->lstfree].evton_val == 2, "Test 1 of callbacks and user data");
    sp_evtstack_destroy(&es);

    sp_evtstack_create(&es, 3);
    sp_evtstack_init(es, init_cb, evton_cb2, evtoff_cb, td_es, sizeof(Test_Data));
    for(i = 0; i < 3; i++) { 
        init_test_vars(&td_es[i]);
        td_es[i].id = i;
    }
    sp_evtstack_add(es, 0, 0, 4, &id);
    tp->v1 = id;
    sp_evtstack_add(es, 0, 0, 4, &id);
    tp->v2 = id;
    sp_evtstack_add(es, 0, 0, 4, &id);
    tp->v3 = id;
    for(i = 0; i <= 5; i++){
        sp_evtstack_update(es, i);
        sp_evtstack_exec(es);
    }
    ok(td_es[2].evton_val == 2
            , "Test 2 of callbacks and user data");
    sp_evtstack_destroy(&es);

    sp_evtstack_create(&es, 3);
    sp_evtstack_init(es, init_cb, evton_cb2, evtoff_cb, td_es, sizeof(Test_Data));
    for(i = 0; i < 3; i++) { 
        init_test_vars(&td_es[i]);
        td_es[i].id = i;
    }
    sp_evtstack_add(es, 0, 0, 4, &id);
    tp->v1 = es->nalloc;

    sp_evtstack_add(es, 0, 4, 4, &id);
    tp->v2 = es->nalloc;

    sp_evtstack_add(es, 0, 8, 4, &id);
    tp->v3 = es->nalloc;

    ok(tp->v1 == 1 && tp->v2 == 2 && tp->v3 == 3 && sp_evtstack_full(es) && 
            es->nxtfree == SPEVSTK_NOFREE
            , "Testing allocation numbers and correlation to SPEVSTK_NOFREE");
    sp_evtstack_destroy(&es);

    sp_evtstack_create(&es, 4);
    sp_evtstack_init(es, init_cb, evton_cb2, evtoff_cb, td_es, sizeof(Test_Data));
    ok(es->evt[0].mode == SPEVT_FREE, "Eventstack init bug check.");
    sp_evtstack_destroy(&es);

    return 0;
}
