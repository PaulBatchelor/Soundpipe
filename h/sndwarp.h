
typedef struct sp_sndwarp_warpsection sp_sndwarp_warpsection;

typedef struct {
    SPFLOAT r1, r2, amp, timewarp, resample, isampfun, ibegin,
          iwsize, irandw, ioverlap, ifn, itimemode;
    sp_ftbl *ftpWind, *ftpSamp;
    int32_t maxFr, prFlg, flen, sampflen, nsections;
    int32_t chans, *frPtr, begin;
    sp_sndwarp_warpsection *exp;
    sp_auxdata auxch;
    int16_t   ampcode, timewarpcode, resamplecode;
} sp_sndwarp;

int sp_sndwarp_create(sp_sndwarp **p);
int sp_sndwarp_destroy(sp_sndwarp **p);
int sp_sndwarp_init(sp_data *sp,
                    sp_sndwarp *p,
                    sp_ftbl *ft1,
                    SPFLOAT ibegin,
                    int32_t iwsize,
                    SPFLOAT irandw,
                    int32_t ioverlap,
                    sp_ftbl *ft2,
                    SPFLOAT itimemode);
int sp_sndwarp_compute(sp_data *sp, sp_sndwarp *p, SPFLOAT *in, SPFLOAT *out);
