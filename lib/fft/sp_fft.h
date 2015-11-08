typedef struct {
    SPFLOAT *utbl;
    int16_t *BRLow;
} fft;

void sp_fft_create(sp_fft **fft);
void sp_fft_init(sp_fft *fft, int M);
void sp_fftr(sp_fft *fft, SPFLOAT *buf, int FFTsize);
void sp_ifftr(sp_fft *fft, SPFLOAT *buf, int FFTsize);
void sp_fft_destroy(sp_fft *fft);
