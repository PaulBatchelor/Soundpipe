/*
 * Granule
 *
 * This code has been extracted from the Csound opcode "granule".
 * It has been modified to work as a Soundpipe module.
 *
 * Original Author(s): Allan S C Lee, John ffitch
 * Year: 1994, 1995
 * Location: Opcodes/sndwarp.c
 */

#include <stdlib.h>
#include "soundpipe.h"

int sp_granule_create(sp_granule **p)
{
    *p = malloc(sizeof(sp_granule));
    return SP_OK;
}

int sp_granule_destroy(sp_granule **p)
{
    free(*p);
    return SP_OK;
}

int sp_granule_init(sp_data *sp, sp_granule *p,
                    SPFLOAT ivoice,
                    SPFLOAT imode,
                    SPFLOAT ithd,
                    sp_ftbl *ft,
                    SPFLOAT ipshift,
                    SPFLOAT igskip,
                    SPFLOAT igskip_os,
                    SPFLOAT igsize_os,
                    SPFLOAT iatt,
                    SPFLOAT idec,
                    SPFLOAT iseed,
                    SPFLOAT ipitch1,
                    SPFLOAT ipitch2,
                    SPFLOAT ipitch3,
                    SPFLOAT ipitch4,
                    sp_ftbl *ft_env)
{
    return SP_OK;
}

int sp_granule_compute(sp_data *sp, sp_granule *p, SPFLOAT *in, SPFLOAT *out)
{
    return SP_OK;
}
