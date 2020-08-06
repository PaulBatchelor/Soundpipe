typedef struct {
    SPFLOAT freq, bw;
    SPFLOAT lfreq, lbw;
    SPFLOAT a[7];
    SPFLOAT pidsr, tpidsr;
} sp_butbr;

int sp_butbr_create(sp_butbr **p);
int sp_butbr_destroy(sp_butbr **p);
int sp_butbr_init(sp_data *sp, sp_butbr *p);
int sp_butbr_compute(sp_data *sp, sp_butbr *p, SPFLOAT *in, SPFLOAT *out);
