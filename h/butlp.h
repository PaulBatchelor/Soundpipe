typedef struct  {
    SPFLOAT sr, freq;
    SPFLOAT lfreq;
    SPFLOAT a[7];
    SPFLOAT pidsr;
} sp_butlp;

int sp_butlp_create(sp_butlp **p);
int sp_butlp_destroy(sp_butlp **p);
int sp_butlp_init(sp_data *sp, sp_butlp *p);
int sp_butlp_compute(sp_data *sp, sp_butlp *p, SPFLOAT *in, SPFLOAT *out);
