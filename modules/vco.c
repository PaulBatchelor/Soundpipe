/*
 * VCO
 * 
 * This code has been extracted from the Csound opcode "vco".
 * It has been modified to work as a Soundpipe module.
 * 
 * Original Author(s): Hans Mikelson
 * Year: 1998
 * Location: Opcodes/biquad.c
 *
 */

#include <stdlib.h>
#include "soundpipe.h"

int sp_vco_create(sp_vco **p)
{
    *p = malloc(sizeof(sp_vco));
    return SP_OK;
}

int sp_vco_destroy(sp_vco **p)
{
    sp_vco *pp = *p;
    sp_auxdata_free(&pp->aux);
    sp_ftbl_destroy(&pp->ftp);
    free(*p);
    return SP_OK;
}

int sp_vco_init(sp_data *sp, sp_vco *p)

{
    p->amp = 0.3;
    p->freq = 440;
    p->wave = 1.0;
    p->maxd = 1;
    p->iphs = 0;
    p->leak = 1; 
    p->inyq = 0.5;
    p->pw = 0.5;     
    uint32_t ndel = (uint32_t)(p->maxd * sp->sr);

    sp_ftbl_create(sp, &p->ftp, 4096); 
    sp_gen_sine(p->ftp);

    if (p->iphs >= 0.0)
      p->lphs = (int32_t)(p->iphs * 0.5 * SP_FT_MAXLEN);
    else {
      printf("Initial value of lphs set to zero\n");
      p->lphs = 0;
    }

      p->ynm1 = (p->wave == 1.0) ? -0.5 : 0.0;
      p->ynm2 = 0.0;

    if (ndel == 0) ndel = 1;    /* fix due to Troxler */

    sp_auxdata_alloc(&p->aux, ndel * sizeof(SPFLOAT));

    p->left = 0;

    if (p->leak <= 0.0 || p->leak >= 1.0) {
      p->leaky = (p->wave == 3.0) ? 0.995 : 0.999;
    } else {
      p->leaky = p->leak;
    }
    p->nyq = p->inyq;

    return SP_OK;
}

int sp_vco_compute(sp_data *sp, sp_vco *p, SPFLOAT *in, SPFLOAT *out)
{
    sp_ftbl *ftp;
    SPFLOAT *ftbl;
    int32_t  phs, inc, lobits, dwnphs, tnp1, lenmask, maxd, indx, n;
    SPFLOAT leaky, amp, fqc;
    SPFLOAT sicvt2, over2n, scal, num, denom, pulse = 0.0, saw = 0.0;
    SPFLOAT sqr = 0.0, tri = 0.0;
    int knh;

    SPFLOAT *buf = (SPFLOAT *)p->aux.ptr;
    SPFLOAT fv1, out1;
    int32_t v1, v2;
    int wave = (int32_t) (p->wave);

    leaky = p->leaky;

    ftp = p->ftp;
    maxd = (uint32_t) (p->maxd * sp->sr);
    if (maxd == 0) maxd = 1;
    indx = p->left;

    ftbl = ftp->tbl;
    sicvt2 = ftp->sicvt * 0.5;
    lobits = ftp->lobits;
    lenmask = ftp->size - 1;
    fqc = p->freq;
    knh = (int)(sp->sr * p->nyq / fqc);

    if ((n = (int)knh) <= 0) {
        fprintf(stderr, "knh=%x nyq=%f fqc=%f\n"
        "vco knh (%d) <= 0; taken as 1\n", knh, p->nyq, fqc, n);
        n = 1;
    }
    tnp1 = n + n + 1;
    over2n = 0.5 / n;

    amp  = p->amp;
    scal = over2n;
    inc = (int32_t)(fqc * sicvt2);
    phs = p->lphs;
    /*-----------------------------------------------------*/
    /* PWM Wave                                            */
    /*-----------------------------------------------------*/
    if (wave == 2) {
        SPFLOAT pw = p->pw;
        dwnphs = phs >> lobits;
        denom = *(ftbl + dwnphs);
        if (denom > 0.00001 || denom < -0.00001) {
        num = *(ftbl + (dwnphs * tnp1 & lenmask));
        pulse = (num / denom - 1.0) * scal;
        }
        else pulse = 1.0;
        phs += inc;
        phs &= SP_FT_PHMASK;
        buf[indx] = pulse;
        fv1 = (SPFLOAT) indx - sp->sr * pw / fqc;

        v1 = (int32_t) fv1;
        if (fv1 < 0.0) v1--;
        fv1 -= (SPFLOAT) v1;

        /* Make sure Inside the buffer */
        while (v1 >= maxd)
        v1 -= maxd;
        while (v1 < 0L)
        v1 += maxd;

        /* Find next sample for interpolation */

        v2 = (v1 < (maxd - 1L) ? v1 + 1L : 0L);
        out1 = buf[v1] + fv1 * (buf[v2] - buf[v1]);

        if (++indx == maxd) indx = 0; 
        /* End of VDelay */

        sqr  = pulse - out1 + leaky*p->ynm1;
        p->ynm1 = sqr;
        *out  = (sqr + pw - 0.5) * 1.9 * amp;
    }

    /*-----------------------------------------------------*/
    /* Triangle Wave                                       */
    /*-----------------------------------------------------*/
    else if (wave == 3) {
        SPFLOAT pw = p->pw;
        dwnphs = phs >> lobits;
        denom = *(ftbl + dwnphs);
        if (denom > 0.0002 || denom < -0.0002) {
            num = *(ftbl + (dwnphs * tnp1 & lenmask));
            pulse = (num / denom - 1.0) * scal;
        }
        else pulse = 1.0;
        phs += inc;
        phs &= SP_FT_PHMASK;

        buf[indx] = pulse;
        fv1 = (SPFLOAT) indx - sp->sr * pw / fqc;

        v1 = (int32_t) fv1;
        if (fv1 < 0.0) v1--;
        fv1 -= (SPFLOAT) v1;
        /* Make sure Inside the buffer */
        while (v1 >= maxd) v1 -= maxd;
        while (v1 < 0L) v1 += maxd;

        /* Find next sample for interpolation */
        v2 = (v1 < (maxd - 1L) ? v1 + 1L : 0L);
        out1 = buf[v1] + fv1 * (buf[v2] - buf[v1]);

        if (++indx == maxd) indx = 0;
        /* End of VDelay */

        /* Integrate twice and ouput */
        sqr = pulse - out1 + leaky*p->ynm1;
        tri = sqr + leaky*p->ynm2;
        p->ynm1 = sqr;
        p->ynm2 = tri;
        *out = tri * amp * fqc
        / (sp->sr * 0.42 * (0.05 + pw - pw * pw));
    }
    /*-----------------------------------------------------*/
    /* Sawtooth Wave                                       */
    /*-----------------------------------------------------*/
    else {
        dwnphs = phs >> lobits;
        denom = *(ftbl + dwnphs);
        if (denom > 0.0002 || denom < -0.0002) {
            num = *(ftbl + (dwnphs * tnp1 & lenmask));
            pulse = (num / denom - 1.0) * scal;
        }
        /* else pulse = *ampp; */
        else pulse = 1.0;

        phs += inc;
        phs &= SP_FT_PHMASK;
        saw  = pulse + leaky*p->ynm1;
        p->ynm1 = saw;
        *out = saw * 1.5 * amp;
    }

    p->left = indx;
    p->lphs = phs;
    return SP_OK;
}
