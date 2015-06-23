#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "base.h"

int sp_create(sp_data **spp) 
{
    *spp = (sp_data *) malloc(sizeof(sp_data));
    sp_data *sp = *spp;
    sprintf(sp->filename, "test.wav");
    SPFLOAT *out = malloc(sizeof(SPFLOAT));
    *out = 0;
    sp->out = out;
    sp->sr = 44100;
    sp->len = 5 * sp->sr;
    sp->pos = 0;
    return 0;
}

int sp_destroy(sp_data **spp)
{
    sp_data *sp = *spp;
    free(sp->out);
    free(*spp);
    return 0;
}

int sp_process(sp_data *sp, void *ud, void (*callback)(sp_data *, void *))
{

    /* is buf still needed? */
    SF_INFO info;
    SPFLOAT buf[SP_BUFSIZE];
    info.samplerate = sp->sr;
    info.channels = 1;
    info.format = SF_FORMAT_WAV | SF_FORMAT_FLOAT;
    int numsamps, i;

    sp->sf = sf_open(sp->filename, SFM_WRITE, &info);

    while(sp->len > 0){
        if(sp->len < SP_BUFSIZE) {
            numsamps = sp->len;
        }else{
            numsamps = SP_BUFSIZE;
        }
        for(i = 0; i < numsamps; i++){
            callback(sp, ud);
            buf[i] = sp->out[0];
            sp->pos++;
        }
        sf_write_float(sp->sf, buf, numsamps);
        sp->len -= numsamps;
    }
    sf_close(sp->sf);
    return 0;
}

int sp_auxdata_alloc(sp_auxdata *aux, size_t size)
{
    aux->ptr = malloc(size);
    aux->size = size;
    memset(aux->ptr, 0, size);
    return SP_OK;
}

int sp_auxdata_free(sp_auxdata *aux)
{
    free(aux->ptr);
    return SP_OK;
}

int sp_auxdata_getbuf(sp_auxdata *aux, uint32_t pos, SPFLOAT *out)
{
    if(pos * sizeof(SPFLOAT) > aux->size){
        fprintf(stderr, "Error: Buffer overflow!\n");
        *out = 0;
        return SP_NOT_OK;
    }else{
        SPFLOAT *tmp = aux->ptr; 
        *out = tmp[pos];
    }
    return SP_OK;

}

int sp_auxdata_setbuf(sp_auxdata *aux, uint32_t pos, SPFLOAT *in)
{
    if((pos * sizeof(SPFLOAT)) > aux->size){
        fprintf(stderr, "Error: Buffer overflow!\n");
        return SP_NOT_OK;
    }else{
        SPFLOAT *tmp = aux->ptr; 
        SPFLOAT n = *in;
        tmp[pos] = n;
    }
    return SP_OK;
}

SPFLOAT sp_midi2cps(int nn) 
{
    return pow(2, (nn - 69.0) / 12.0) * 440.0;
}
