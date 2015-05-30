#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "soundpipe.h" 
int sp_ftbl_create(sp_ftbl **ft, size_t size) {
    *ft = malloc(sizeof(sp_ftbl));
    sp_ftbl *ftp = *ft;
    ftp->size = size;
    ftp->tbl = malloc(sizeof(SPFLOAT) * size);
    memset(ftp->tbl, 0, sizeof(SPFLOAT) * size);
    return SP_OK;
}
int sp_ftbl_destroy(sp_ftbl **ft){
    sp_ftbl *ftp = *ft;
    free(ftp->tbl);
    free(*ft);
    return SP_OK;
}
int sp_gen_sine(sp_ftbl *ft){
    unsigned long i;
    SPFLOAT step = 2 * M_PI / ft->size;
    for(i = 0; i < ft->size; i++){
        ft->tbl[i] = sin(i * step);
    }
    return SP_NOT_OK;
}
