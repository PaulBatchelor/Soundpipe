#include <stdio.h>
#include <stdbool.h>
#include "tap.h"
#include "base.h"
#include "ftbl.h"


int main( int argc, char** argv ) {
    plan( 3 );

    int status;
    sp_data *sp;
    sp_create(&sp);
    sp_ftbl *ft; 

    status = sp_ftbl_create(sp, &ft, 1024);

    ok(status, "Initialize event");

    if(!status){
        printf("Cannot go futher until event has been initalized. Exiting...\n");
        return 1;    
    };

    ok(ft->size == 1024 && ft->tbl[501] == 0, "Table is properly intialized");
    sp_gen_sine(ft);

    sp_ftbl_destroy(&ft);
    sp_destroy(&sp);
    return 0;
}
