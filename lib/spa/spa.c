#include <stdio.h>
#include <stdint.h>
#include "soundpipe.h"

#define CHECK_NULL_FILE(fp) if(fp == NULL) return SP_NOT_OK

int spa_open(sp_data *sp, sp_audio *spa, const char *name, int mode)
{
    spa->mode = SPA_NULL;
    spa_header *header = &spa->header;
    spa->offset = sizeof(spa_header);
    if(mode == SPA_READ) {
        spa->fp = fopen(name, "rb");
        CHECK_NULL_FILE(spa->fp);
        fread(header, spa->offset, 1, spa->fp);
    } else if(mode == SPA_WRITE) {
        spa->fp = fopen(name, "wb");
        CHECK_NULL_FILE(spa->fp);
        header->magic = 100;
        header->nchan = sp->nchan;
        header->len = sp->len;
        header->sr = sp->sr;
        fwrite(header, spa->offset, 1, spa->fp);
    } else {
        return SP_NOT_OK;
    }

    spa->mode = mode;

    return SP_OK;
}

size_t spa_write_buf(sp_data *sp, sp_audio *spa, SPFLOAT *buf, uint32_t size)
{
    if(spa->mode != SPA_WRITE) {
        return 0;
    }
    return fwrite(buf, sizeof(SPFLOAT), size, spa->fp);
}

size_t spa_read_buf(sp_data *sp, sp_audio *spa, SPFLOAT *buf, uint32_t size)
{
    if(spa->mode != SPA_READ) {
        return 0;
    }
    return fread(buf, sizeof(SPFLOAT), size, spa->fp);
}

int spa_close(sp_audio *spa)
{
    if(spa->fp != NULL) fclose(spa->fp);
    return SP_OK;
}
