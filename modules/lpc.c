#include <stdlib.h>
#include "soundpipe.h"
#include "openlpc.h"

int sp_lpc_create(sp_lpc **lpc)
{
    *lpc = malloc(sizeof(sp_lpc));
    return SP_OK;
}

int sp_lpc_destroy(sp_lpc **lpc)
{
    sp_lpc *plpc;
    plpc = *lpc;
    sp_auxdata_free(&plpc->m_e);
    sp_auxdata_free(&plpc->m_d);
    sp_auxdata_free(&plpc->m_out);
    sp_auxdata_free(&plpc->m_in);
    free(*lpc);
    return SP_OK;
}

int sp_lpc_init(sp_data *sp, sp_lpc *lpc, int framesize)
{
    int i;
    lpc->counter = 0;
    lpc->clock = 0;
    lpc->block = 4;
    lpc->samp = 0;
    lpc->framesize = framesize;
    openlpc_sr(sp->sr / lpc->block);

    sp_auxdata_alloc(&lpc->m_d, openlpc_get_decoder_state_size());
    sp_auxdata_alloc(&lpc->m_e, openlpc_get_encoder_state_size());
    lpc->d = lpc->m_d.ptr;
    lpc->e = lpc->m_e.ptr;

    sp_auxdata_alloc(&lpc->m_in, sizeof(short) * framesize);
    sp_auxdata_alloc(&lpc->m_out, sizeof(short) * framesize);

    lpc->out = lpc->m_out.ptr;
    lpc->in = lpc->m_in.ptr;

    init_openlpc_decoder_state(lpc->d, framesize);
    init_openlpc_encoder_state(lpc->e, framesize);

    for(i = 0; i < framesize; i++) {
        lpc->in[i] = 0;
        lpc->out[i] = 0;
        if(i < 7) lpc->data[i] = 0;
    }
    return SP_OK;
}

int sp_lpc_compute(sp_data *sp, sp_lpc *lpc, SPFLOAT *in, SPFLOAT *out)
{
    if(lpc->clock == 0) {
        if(lpc->counter == 0) {

            openlpc_encode(lpc->in, lpc->data, lpc->e);
            openlpc_decode(lpc->data, lpc->out, lpc->d);
        }

        lpc->in[lpc->counter] = *in * 32767; 
        lpc->samp = lpc->out[lpc->counter] / 32767.0;

        lpc->counter = (lpc->counter + 1) % lpc->framesize;
    }

    lpc->clock = (lpc->clock + 1) % lpc->block;
    *out = lpc->samp;

    return SP_OK;
}
