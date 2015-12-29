/*
 * Foo
 * 
 * This is a dummy module. It doesn't do much.
 * Feel free to use this as a boilerplate template.
 * 
 */

#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "soundpipe.h"

static inline int buf_bytes_alloc(int nChannels, int partSize, int nPartitions)
{
    int nSmps;

    nSmps = (partSize << 1);                                /* tmpBuf     */
    nSmps += ((partSize << 1) * nPartitions);               /* ringBuf    */
    nSmps += ((partSize << 1) * nChannels * nPartitions);   /* IR_Data    */
    nSmps += ((partSize << 1) * nChannels);                 /* outBuffers */

    return ((int) sizeof(SPFLOAT) * nSmps);
}

static void set_buf_pointers(sp_conv *p,
                             int nChannels, int partSize, int nPartitions)
{
    SPFLOAT *ptr;
    int   i;

    ptr = (SPFLOAT *) (p->auxData.ptr);
    p->tmpBuf = ptr;
    ptr += (partSize << 1);
    p->ringBuf = ptr;
    ptr += ((partSize << 1) * nPartitions);
    for (i = 0; i < nChannels; i++) {
      p->IR_Data[i] = ptr;
      ptr += ((partSize << 1) * nPartitions);
    }
    for (i = 0; i < nChannels; i++) {
      p->outBuffers[i] = ptr;
      ptr += (partSize << 1);
    }
}

int sp_conv_create(sp_conv **p)
{
    *p = malloc(sizeof(sp_conv));
    return SP_OK;
}

int sp_conv_destroy(sp_conv **p)
{
    free(*p);
    return SP_OK;
}

int sp_conv_init(sp_data *sp, sp_conv *p, sp_ftbl *ft)
{
    int     i, j, k, n, nBytes, skipSamples;
    SPFLOAT FFTscale;

    /* Soundpipe defaults */
    p->iSkipInit = 0;
    p->iSkipSamples = 0;
    p->iPartLen = 2048;
    //p->iTotLen = 0;

    /* check parameters */
    p->nChannels = 1;
    /* partition length */
    p->partSize = lrintf(p->iPartLen);
    if (p->partSize < 4 || (p->partSize & (p->partSize - 1)) != 0) {
        fprintf(stderr, "conv: invalid partition size.\n");
        return SP_NOT_OK;  
    }
    
    sp_fft_init(&p->fft, log2(p->partSize));
    n = (int) ft->size / p->nChannels;
    skipSamples = lrintf(p->iSkipSamples);
    n -= skipSamples;
    if (lrintf(p->iTotLen) > 0 && n > lrintf(p->iTotLen))
      n = lrintf(p->iTotLen);
    if (n <= 0) {
        return SP_NOT_OK;
    }
    p->nPartitions = (n + (p->partSize - 1)) / p->partSize;
    /* calculate the amount of aux space to allocate (in bytes) */
    nBytes = buf_bytes_alloc(p->nChannels, p->partSize, p->nPartitions);
    sp_auxdata_alloc(&p->auxData, nBytes);
    /* if skipping samples: check for possible truncation of IR */
    /* initialise buffer pointers */
    set_buf_pointers(p, p->nChannels, p->partSize, p->nPartitions);
    /* clear ring buffer to zero */
    n = (p->partSize << 1) * p->nPartitions;
    memset(p->ringBuf, 0, n*sizeof(SPFLOAT));
    /* for (i = 0; i < n; i++) */
    /*   p->ringBuf[i] = FL(0.0); */
    /* initialise buffer index */
    p->cnt = 0;
    p->rbCnt = 0;
    /* calculate FFT of impulse response partitions, in reverse order */
    /* also apply FFT amplitude scale here */
    //FFTscale = csound->GetInverseRealFFTScale(csound, (p->partSize << 1));
    FFTscale = 1.0;
    for (j = 0; j < p->nChannels; j++) {
      i = (skipSamples * p->nChannels) + j;           /* table read position */
      n = (p->partSize << 1) * (p->nPartitions - 1);  /* IR write position */
      do {
        for (k = 0; k < p->partSize; k++) {
          if (i >= 0 && i < (int) ft->size)
            p->IR_Data[j][n + k] = ft->tbl[i] * FFTscale;
          else
            p->IR_Data[j][n + k] = 0.0;
          i += p->nChannels;
        }
        /* pad second half of IR to zero */
        for (k = p->partSize; k < (p->partSize << 1); k++)
          p->IR_Data[j][n + k] = 0.0;
        /* calculate FFT */
        //csound->RealFFT(csound, &(p->IR_Data[j][n]), (p->partSize << 1));
        sp_fftr(&p->fft, &(p->IR_Data[j][n]), (p->partSize << 1));
        n -= (p->partSize << 1);
      } while (n >= 0);
    }
    /* clear output buffers to zero */
    for (j = 0; j < p->nChannels; j++) {
      for (i = 0; i < (p->partSize << 1); i++)
        p->outBuffers[j][i] = 0.0;
    }
    p->initDone = 1;

    return SP_OK;
}

int sp_conv_compute(sp_data *sp, sp_conv *p, SPFLOAT *in, SPFLOAT *out)
{
    /* Send the signal's input to the output */
    *out = *in;
    return SP_OK;
}
