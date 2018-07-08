#include <stdlib.h>
#include "soundpipe.h"
#include "dr_wav.h"

int sp_ftbl_loadwav(sp_data *sp, sp_ftbl **ft, const char *filename)
{
    drwav wav;
    size_t size;
    SPFLOAT *tbl;
    drwav_init_file(&wav, filename);
    size = wav.totalSampleCount;
    ft = malloc(sizeof(sp_ftbl));
    (*ft)->tbl = malloc(sizeof(SPFLOAT) * (size + 1));
    tbl = (*ft)->tbl;
    sp_ftbl_init(sp, *ft, size);
    drwav_read_f32(&wav, size, tbl);
    drwav_uninit(&wav);
    return SP_OK;
}
