typedef struct {
    SPFLOAT freq, bw;
    SPFLOAT lfreq, lbw;
    SPFLOAT a[7];
    SPFLOAT pidsr, tpidsr;
} sp_butbp;

int sp_butbp_create(sp_butbp **p);
int sp_butbp_destroy(sp_butbp **p);
int sp_butbp_init(sp_data *sp, sp_butbp *p);
int sp_butbp_compute(sp_data *sp, sp_butbp *p, SPFLOAT *in, SPFLOAT *out);
