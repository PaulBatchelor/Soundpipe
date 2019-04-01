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
#include <math.h>
#include "soundpipe.h"

#define RNDMUL 15625L
#define DV32768 0.000030517578125

static SPFLOAT grand(sp_granule *p)
{
   p->grnd *= (int32_t
               )RNDMUL;
   p->grnd += 1;
   return ((SPFLOAT) p->grnd * DV32768);  /* IV - Jul 11 2002 */
} /* end grand(p) */


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
                    SPFLOAT iratio,
                    SPFLOAT imode,
                    SPFLOAT ithd,
                    sp_ftbl *ft,
                    SPFLOAT ipshift,
                    SPFLOAT igskip,
                    SPFLOAT igskip_os,
                    SPFLOAT igsize_os,
                    SPFLOAT ilength,
                    SPFLOAT igap_os,
                    SPFLOAT iatt,
                    SPFLOAT idec,
                    SPFLOAT iseed,
                    SPFLOAT ipitch1,
                    SPFLOAT ipitch2,
                    SPFLOAT ipitch3,
                    SPFLOAT ipitch4,
                    sp_ftbl *ft_env)
{
    sp_ftbl *ftp;
    int32_t nvoice, cnt;
    int32_t tmplong1, tmplong2;
    SPFLOAT tmpfloat1;
    SPFLOAT pitch[4];

    p->ftp = ft;
    ftp = ft;
    p->ftp_env = ft_env;

    if (ivoice > SP_GRANULE_MAXVOICE) {
        fprintf(stderr,
                "Granule: too many voices requested. Setting to %d\n",
                SP_GRANULE_MAXVOICE);
        ivoice = SP_GRANULE_MAXVOICE;
    }

    p->ivoice = SP_GRANULE_MAXVOICE;


    if (iratio <= 0) {
        fprintf(stderr, "Granule: iratio invalid. Setting to 1\n");
        iratio = 1;
    }

    p->iratio = iratio;

    if ((imode != 0) && ((imode != -1) && (imode != 1))) {
        fprintf(stderr, "Granule: invalid imode. Defaulting to 0\n");
        imode = 0;
    }

    p->imode = imode;

    if (ithd < 0) {
        fprintf(stderr, "Granule: ithd must be greater than 0. Using 0.5\n");
        ithd = 0.5;
    }

    p->ithd = ithd;

    if ((ipshift != 1) &&
        (ipshift!=2) &&
        (ipshift!=3) &&
        (ipshift!=4) &&
        (ipshift!=0)) {
        fprintf(stderr, "ipshift must be between 0 and 4. Using 0.\n");
        ipshift = 0;
    }

    p->ipshift = ipshift;

    if ((((p->ipshift >=1) && (p->ipshift <=4)) &&
                 (p->ivoice < p->ipshift))) {
        fprintf(stderr, "granule_set: Not enough voices "
                        "for the number of pitches");
        /* TODO: set defaults that mitigate this error */

    }
    if (p->ipshift != 0.0) {
        if (ipitch1 < 0.0) {
            fprintf(stderr, "Pitch1 must be greater than 0. Using 1.\n");
            ipitch1 = 1;
        }
        if (ipitch2 < 0.0) {
            fprintf(stderr, "Pitch2 must be greater than 0. Using 1.\n");
            ipitch2 = 1;
        }
        if (ipitch3 < 0.0) {
            fprintf(stderr, "Pitch3 must be greater than 0. Using 1.\n");
            ipitch3 = 1;
        }
        if (ipitch4 < 0.0) {
            fprintf(stderr, "Pitch4 must be greater than 0. Using 1.\n");
            ipitch4 = 1;
        }
    }

    p->ipitch1 = ipitch1;
    p->ipitch2 = ipitch2;
    p->ipitch3 = ipitch3;
    p->ipitch4 = ipitch4;

    if (igskip < 0 || (igskip * sp->sr) > ft->size) {
        fprintf(stderr, "igksip is out of bounds. Setting to 0\n");
        igskip = 0;
    }

    p->igskip = igskip;

    if (igskip_os < 0) {
      fprintf(stderr, "igskip_os must be greater than 0\n");
    }

    p->igskip = igskip;

    p->ilength = ilength;
    p->gstart = (int32_t)(p->igskip * sp->sr);
    p->glength = (int32_t)(p->ilength * sp->sr);
    p->gend = p->gstart + p->glength;

    if (igap_os < 0 || igap_os > 100) {
        fprintf(stderr, "igap_os must be between 0 and 100\n");
        igap_os = 0;
    }

    p->igap_os = igap_os;

    if (igsize_os < 0 || igsize_os >100) {
        fprintf(stderr, "igsize_os must be between 0 and 100\n");
        igsize_os = 0;
    }

    p->igsize_os = igsize_os;

    if (iatt < 0.0 || p->idec < 0.0 ||
                 ((iatt + idec) > 100.0)) {
        fprintf(stderr, "Invalid values for iatt and idec\n");
    }

    p->iseed = iseed;
    if (p->iseed >=0) {
        p->grnd = (int16_t)(p->iseed * 32768.0);       /* IV - Jul 11 2002 */
    }


                                /* Initialize variables....*/
    p->gskip_os = (int32_t)(p->igskip_os * sp->sr);/* in number of samples */
    p->gap_os = p->igap_os / 100.0;
    p->gsize_os = p->igsize_os / 100.0;

    for (nvoice = 0; nvoice < p->ivoice; nvoice++) {
        p->fpnt[nvoice] = 0;
        p->cnt[nvoice]  = 0;
        p->phs[nvoice]  = 0.0;
        p->gskip[nvoice] = (int32_t)(p->igskip * sp->sr);
        p->gap[nvoice] = (int32_t)(p->kgap * sp->sr);
    }

    if (p->igap_os != 0) {
      for (nvoice = 0; nvoice < p->ivoice; nvoice++)
        p->gap[nvoice] += (int32_t)((SPFLOAT)p->gap[nvoice] * p->gap_os * grand(p));
    }

    if (p->imode == 0) {
        for (nvoice = 0; nvoice < p->ivoice; nvoice++)
            p->mode[nvoice] = (grand(p) < 0) ? -1 : 1;
    } else {
        for (nvoice = 0; nvoice < p->ivoice; nvoice++)
            p->mode[nvoice] = (int32_t)p->imode;
    }

    if ((p->ipshift >=1) && (p->ipshift <=4)) {
        pitch[0] = p->ipitch1;
        pitch[1] = p->ipitch2;
        pitch[2] = p->ipitch3;
        pitch[3] = p->ipitch4;
        cnt = 0;
        for (nvoice = 0; nvoice < p->ivoice; nvoice++) {
            p->pshift[nvoice] = pitch[cnt++];
            cnt = (cnt < p->ipshift) ? cnt : 0;
        }
    }
    if (p->ipshift == 0) {
        for (nvoice = 0; nvoice < p->ivoice; nvoice++) {
            tmpfloat1 = grand(p);
            p->pshift[nvoice] =
              (tmpfloat1 <0.0) ? (tmpfloat1*0.5)+1.0 : tmpfloat1+1.0f;
        }
    }

    for (nvoice = 0; nvoice < p->ivoice; nvoice++)
        p->gsize[nvoice] = (int32_t)(p->kgsize * sp->sr * p->pshift[nvoice]);

    if (p->igsize_os != 0) {
        for (nvoice = 0; nvoice < p->ivoice; nvoice++)
            p->gsize[nvoice] += (int32_t)(p->gsize[nvoice] *
                                          p->gsize_os * grand(p));
    }

    for (nvoice = 0; nvoice < p->ivoice; nvoice++)
      p->stretch[nvoice] = p->gsize[nvoice] + p->gap[nvoice];

    if (p->igskip_os != 0) {
        for (nvoice = 0; nvoice < p->ivoice; nvoice++) {
            tmplong1 = ((p->gskip_os * grand(p)) + (SPFLOAT)p->gskip[nvoice]);
            p->gskip[nvoice] =
            (tmplong1 < p->gstart) ? p->gstart : tmplong1;
            p->gskip[nvoice]=
            ((p->gskip[nvoice]+p->stretch[nvoice])>(int32_t)p->gend) ?
            (int32_t)p->gstart :
            p->gskip[nvoice];
        }
    }

    if (p->ithd != 0) {
        tmplong2 = 0;
        for (tmplong1=0; tmplong1< (int32_t) ftp->size; tmplong1++) {
            if (fabs(ftp->tbl[tmplong1]) >= p->ithd )
                ftp->tbl[tmplong2++] = ftp->tbl[tmplong1];
        }
        ftp->size = tmplong2;
    }

    if (p->gend > (int32_t) ftp->size) {
        fprintf(stderr, "Granule: illegal combination of igskip and ilength\n");
    }

    nvoice = (int32_t)p->ivoice;

    /* if (UNLIKELY(*p->ilength < (20 * *p->kgsize))) { */
    /*   csound->Warning(csound, Str("granule_set: " */
    /*                               "WARNING * ilength may be too short *\n" */
    /*                               "            ilength should be " */
    /*                               "greater than kgsize * max up\n" */
    /*                               "            pitch shift. Also, igsize_os " */
    /*                               "and igskip_os should\n" */
    /*                               "            be taken into consideration.\n" */
    /*                               "ilength is " */
    /*                               "%f Sec, kgsize is %f Sec\n"), */
    /*                   *p->ilength, *p->kgsize); */

    return SP_OK;
}

int sp_granule_compute(sp_data *sp, sp_granule *p, SPFLOAT *in, SPFLOAT *out)
{
    return SP_OK;
}
