/*
 * Jitter
 * 
 * This code has been extracted from the Csound opcode "jitter".
 * It has been modified to work as a Soundpipe module.
 * 
 * Original Author(s): Gabriel Maldonado
 * Year: 1998
 * Location: Opcodes/uggab.c
 *
 */

#include <stdlib.h>
#include "soundpipe.h"

int sp_jitter_create(sp_jitter **p)
{
    *p = malloc(sizeof(sp_jitter));
    return SP_OK;
}

int sp_jitter_destroy(sp_jitter **p)
{
    free(*p);
    return SP_OK;
}

int sp_jitter_init(sp_data *sp, sp_jitter *p)
{

    p->num2     = BiRandGab;
    p->initflag = 1;
    p->phs=0;
    return SP_OK;
}

int sp_jitter_compute(sp_data *sp, sp_jitter *p, SPFLOAT *in, SPFLOAT *out)
{
    if (p->initflag) {
      p->initflag = 0;
      *p->ar = p->num2 * *p->amp;
      goto next;
    }
    *p->ar = (p->num1 + (MYFLT)p->phs * p->dfdmax) * *p->amp;
    p->phs += (int32)(p->xcps * CS_KICVT);

    if (p->phs >= MAXLEN) {
    next:
      p->xcps   = randGab  * (*p->cpsMax - *p->cpsMin) + *p->cpsMin;
      p->phs   &= PHMASK;
      p->num1   = p->num2;
      p->num2   = BiRandGab;
      p->dfdmax = (p->num2 - p->num1) / FMAXLEN;
    }
    return SP_OK;
}
