#define MAXOUTS 2
typedef struct {
    SPFLOAT out[MAXOUTS], time, amp, pitch, lock, iN,
        idecim, onset, offset, dbthresh;
    int cnt, hsize, curframe, N, decim,tscale;
    unsigned int nchans;
    SPFLOAT pos;
    SPFLOAT accum;
    sp_auxdata outframe[MAXOUTS], win, bwin[MAXOUTS], fwin[MAXOUTS],
    nwin[MAXOUTS], prev[MAXOUTS], framecount[MAXOUTS], indata[2];
    SPFLOAT *tab;
    int curbuf;
    SNDFILE *sf;
    SPFLOAT resamp;
    sp_ftbl *ft;
    sp_fft fft;
} sp_mincer;

int sp_mincer_create(sp_mincer **p);
int sp_mincer_destroy(sp_mincer **p);
int sp_mincer_init(sp_data *sp, sp_mincer *p, sp_ftbl *ft);
int sp_mincer_compute(sp_data *sp, sp_mincer *p, SPFLOAT *in, SPFLOAT *out);
