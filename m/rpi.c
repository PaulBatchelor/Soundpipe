#include <stdlib.h>
#include <aaio.h>
#include "soundrpipe.h"

static int sp_rpi_cb(){
    return 0;
}
void sp_rpi_shutdown (void *arg){
	exit (1);
}

int sp_rpi_process(sp_data *sp, void *ud, void (*callback)(sp_data *, void *)){
    getch();
    return SP_OK;
}
