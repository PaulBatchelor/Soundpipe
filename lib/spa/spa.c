#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
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

int sp_process_spa(sp_data *sp, void *ud, void (*callback)(sp_data *, void *))
{
    sp_audio spa;
    if(spa_open(sp, &spa, sp->filename, SPA_WRITE) == SP_NOT_OK) {
        fprintf(stderr, "Error: could not open file %s.\n", sp->filename);    
    }
    while(sp->len > 0) {
        callback(sp, ud);
        spa_write_buf(sp, &spa, sp->out, sp->nchan);
        sp->len--;
        sp->pos++;
    }
    spa_close(&spa);
    return SP_OK;
}

int sp_ftbl_loadspa(sp_data *sp, sp_ftbl **ft, const char *filename)
{
    *ft = malloc(sizeof(sp_ftbl));
    sp_ftbl *ftp = *ft;

    sp_audio spa;

    spa_open(sp, &spa, filename, SPA_READ);

    size_t size = spa.header.len;

    ftp->tbl = malloc(sizeof(SPFLOAT) * (size + 1));
    sp_ftbl_init(sp, ftp, size);

    spa_read_buf(sp, &spa, ftp->tbl, ftp->size);
    spa_close(&spa);
    return SP_OK;
}

