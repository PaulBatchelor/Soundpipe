#include "soundpipe.h"
typedef struct {
    void (*callback)(sp_data *, void *);
}sp_event; 

typedef struct {

}sp_evt_stack; 

int sp_create_evt_stack(sp_data *sp, int nvoices);
int sp_destroy_evt_stack(sp_data *sp, int nvoices);
