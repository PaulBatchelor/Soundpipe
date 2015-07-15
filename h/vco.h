typedef struct sp_vco {
    SPFLOAT amp, freq, wave, pw, sine, maxd, leak, inyq, iphs;
    SPFLOAT ynm1, ynm2, leaky, nyq;
    int32_t lphs;
    sp_ftbl *ftp;
    sp_auxdata aux;
    int32_t left;
} sp_vco;

int sp_vco_create(sp_vco **p);
int sp_vco_destroy(sp_vco **p);
int sp_vco_init(sp_data *sp, sp_vco *p);
int sp_vco_compute(sp_data *sp, sp_vco *p, SPFLOAT *in, SPFLOAT *out);
