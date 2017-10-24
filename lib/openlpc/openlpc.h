/*
 * LPC subroutine declarations
 */

#ifndef OPENLPC_H
#define OPENLPC_H

#ifdef __cplusplus
extern "C" {
#endif

#define OPENLPC_FRAMESIZE_1_8	    250
#define OPENLPC_FRAMESIZE_1_4	    320
#define OPENLPC_ENCODED_FRAME_SIZE  7

typedef struct openlpc_e_state openlpc_encoder_state;
typedef struct openlpc_d_state openlpc_decoder_state;

openlpc_encoder_state *create_openlpc_encoder_state(void);
void init_openlpc_encoder_state(openlpc_encoder_state *st, int framelen);
int  openlpc_encode(const short *in, unsigned char *out, openlpc_encoder_state *st);
void destroy_openlpc_encoder_state(openlpc_encoder_state *st);

openlpc_decoder_state *create_openlpc_decoder_state(void);
void init_openlpc_decoder_state(openlpc_decoder_state *st, int framelen);
int  openlpc_decode(sp_data *sp, unsigned char *in, short *out, openlpc_decoder_state *st);
void destroy_openlpc_decoder_state(openlpc_decoder_state *st);

void openlpc_sr(float sr);

size_t openlpc_get_encoder_state_size(void);
size_t openlpc_get_decoder_state_size(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* OPENLPC_H */
