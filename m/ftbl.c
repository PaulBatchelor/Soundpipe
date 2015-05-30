#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "soundpipe.h" 
int sp_ftbl_create(sp_data *sp, sp_ftbl **ft, size_t size) {
    *ft = malloc(sizeof(sp_ftbl));
    sp_ftbl *ftp = *ft;
    ftp->size = size;
    ftp->tbl = malloc(sizeof(SPFLOAT) * (size + 1));
    memset(ftp->tbl, 0, sizeof(SPFLOAT) * (size + 1));
    ftp->sicvt = 1.0 * SP_FT_MAXLEN / sp->sr;
    ftp->lobits = log2(SP_FT_MAXLEN / size);
    ftp->lomask = pow(2, ftp->lobits) - 1;
    ftp->lodiv = 1.0 / pow(2, ftp->lobits);
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
    return SP_OK;
}

/*TODO: add error checking, make tests */
int sp_gen_file(sp_ftbl *ft, const char *filename){
    SF_INFO info;
    SNDFILE *snd = sf_open(filename, SFM_READ, &info);
    sf_readf_float(snd, ft->tbl, ft->size);
    sf_close(snd);
    return SP_OK;
}
