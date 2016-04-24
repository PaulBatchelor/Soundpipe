/*
 * PaulStretch
 * 
 * An implementation of the PaulStretch algorithm by Paul Nasca Octavian.
 * This code is based off the Python Numpy/Scipy implementation of 
 * PaulStretch, found here: https://github.com/paulnasca/paulstretch_python
 * 
 */

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <complex.h>
#include "soundpipe.h"
#include "kiss_fftr.h"

#ifndef M_PI
#define M_PI		3.14159265358979323846
#endif

static void compute_block(sp_data *sp, sp_paulstretch *p) {
    uint32_t istart_pos = floor(p->start_pos);
    uint32_t pos; 
    uint32_t i;
    uint32_t windowsize = p->windowsize;
    uint32_t half_windowsize = p->half_windowsize;
    SPFLOAT *buf = p->buf;
    SPFLOAT *hinv_buf = p->hinv_buf;
    SPFLOAT *old_windowed_buf= p->old_windowed_buf;
    SPFLOAT *tbl = p->ft->tbl;
    SPFLOAT *window = p->window;
    SPFLOAT *output= p->output;
    for(i = 0; i < windowsize; i++) {
        pos = istart_pos + i;
        if(pos < p->ft->size) {
            buf[i] = tbl[pos] * window[i];
        } else {
            buf[i] = 0;
        }
    }
    kiss_fftr(p->fft, buf, p->tmp1);
    for(i = 0; i < windowsize / 2; i++) {
        SPFLOAT mag = sqrt(p->tmp1[i].r*p->tmp1[i].r + p->tmp1[i].i*p->tmp1[i].i);
        complex ph = cexpf(I * ((SPFLOAT)sp_rand(sp) / SP_RANDMAX) * 2 * M_PI);
        p->tmp1[i].r = mag * crealf(ph); 
        p->tmp1[i].i = mag * cimagf(ph); 
    }
    kiss_fftri(p->ifft, p->tmp1, buf);
    for(i = 0; i < windowsize; i++) {
        buf[i] *= window[i];
        if(i < half_windowsize) {
            output[i] = (SPFLOAT)(buf[i] + old_windowed_buf[half_windowsize + i]) / windowsize;
            output[i] *= hinv_buf[i];
        }
        old_windowed_buf[i] = buf[i];
    }
    p->start_pos += p->displace_pos;
}

int sp_paulstretch_create(sp_paulstretch **p)
{
    *p = malloc(sizeof(sp_paulstretch));
    return SP_OK;
}

int sp_paulstretch_destroy(sp_paulstretch **p)
{
    sp_paulstretch *pp = *p;
    free(pp->window);
    free(pp->old_windowed_buf);
    free(pp->hinv_buf);
    free(pp->buf);
    free(pp->output);
    kiss_fftr_free(pp->fft);
    kiss_fftr_free(pp->ifft);
    KISS_FFT_FREE(pp->tmp1);
    free(*p);
    return SP_OK;
}

int sp_paulstretch_init(sp_data *sp, sp_paulstretch *p, sp_ftbl *ft, SPFLOAT windowsize)
{
    uint32_t i;
    p->ft = ft;
    p->windowsize = (uint32_t)(sp->sr * windowsize);
    p->stretch = 10;
    if(p->windowsize < 16) {
        p->windowsize = 16;
    }
    p->half_windowsize = p->windowsize / 2;
    p->displace_pos = (p->windowsize * 0.5) / p->stretch;

    p->window = malloc(sizeof(SPFLOAT) * p->windowsize);
    memset(p->window, 0, sizeof(SPFLOAT) * p->windowsize);

    p->old_windowed_buf = malloc(sizeof(SPFLOAT) * p->windowsize);
    memset(p->old_windowed_buf, 0, sizeof(SPFLOAT) * p->windowsize);

    p->hinv_buf = malloc(sizeof(SPFLOAT) * p->half_windowsize);
    memset(p->hinv_buf, 0, sizeof(SPFLOAT) * p->half_windowsize);

    p->buf = malloc(sizeof(SPFLOAT) * p->windowsize);
    memset(p->buf, 0, sizeof(SPFLOAT) * p->windowsize);

    p->output = malloc(sizeof(SPFLOAT) * p->half_windowsize);
    memset(p->output, 0, sizeof(SPFLOAT) * p->half_windowsize);

    /* Create Hann window */
    for(i = 0; i < p->windowsize; i++) {
        p->window[i] = 0.5 - cos(i * 2.0 * M_PI / (p->windowsize - 1)) * 0.5;
    }
    /* creatve inverse hann window */
    SPFLOAT hinv_sqrt2 = (1 + sqrt(0.5)) * 0.5;
    for(i = 0; i < p->half_windowsize; i++) {
        p->hinv_buf[i] = hinv_sqrt2 - (1.0 - hinv_sqrt2) * cos(i * 2.0 * M_PI / p->half_windowsize);
    }

    p->start_pos = 0.0;
    p->counter = 0;

    /* set up kissfft */
    p->fft = kiss_fftr_alloc(p->windowsize, 0, NULL, NULL);
    p->ifft = kiss_fftr_alloc(p->windowsize, 1, NULL, NULL);
    kiss_fft_cpx *tmp1 = malloc(sizeof(kiss_fft_cpx) * p->windowsize);
    memset(tmp1, 0, sizeof(SPFLOAT) * p->windowsize);
    p->tmp1 = tmp1;
    return SP_OK;
}

int sp_paulstretch_compute(sp_data *sp, sp_paulstretch *p, SPFLOAT *in, SPFLOAT *out)
{
    if(p->counter == 0) {
        compute_block(sp, p);
    }
    *out = p->output[p->counter];
    p->counter = (p->counter + 1) % p->half_windowsize;
    
    return SP_OK;
}
