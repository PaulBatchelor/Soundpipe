typedef struct sp_sndwarp_warpsection sp_sndwarp_warpsection;

typedef struct {
    SPFLOAT r1, r2, amp, timewarp, resample, begin,
        wsize, randw, overlap, timemode;
    sp_ftbl *ft_win, *ft_samp;
    int32_t maxFr, prFlg, flen, sampflen, nsections;
    int32_t chans, *frPtr;
    sp_sndwarp_warpsection *exp;
    sp_auxdata auxch;
    int16_t   ampcode, timewarpcode, resamplecode;
} sp_sndwarp;

int sp_sndwarp_create(sp_sndwarp **p);
int sp_sndwarp_destroy(sp_sndwarp **p);
int sp_sndwarp_init(sp_data *sp, sp_sndwarp *p,
                    sp_ftbl *ft_samp, sp_ftbl *ft_win,
                    int32_t maxoverlap);
int sp_sndwarp_compute(sp_data *sp, sp_sndwarp *p, SPFLOAT *in, SPFLOAT *out);
