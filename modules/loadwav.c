#include <stdlib.h>
#include "soundpipe.h"
#include "dr_wav.h"

int sp_ftbl_loadwav(sp_data *sp, sp_ftbl **ft, const char *filename)
{
    drwav wav;
    size_t size;
    SPFLOAT *tbl;
    sp_ftbl *ftp;

    if (!drwav_init_file(&wav, filename)) return SP_NOT_OK;

    size = wav.totalSampleCount;
    *ft = malloc(sizeof(sp_ftbl));
    ftp = *ft;
    ftp->tbl = malloc(sizeof(SPFLOAT) * (size + 1));
    tbl = ftp->tbl;
    sp_ftbl_init(sp, ftp, size);
    drwav_read_f32(&wav, size, tbl);
    drwav_uninit(&wav);
    return SP_OK;
}
