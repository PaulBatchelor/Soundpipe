typedef struct  {
    SPFLOAT freq;
    SPFLOAT lfreq;
    SPFLOAT a[7];
    SPFLOAT pidsr;
} sp_buthp;

int sp_buthp_create(sp_buthp **p);
int sp_buthp_destroy(sp_buthp **p);
int sp_buthp_init(sp_data *sp, sp_buthp *p);
int sp_buthp_compute(sp_data *sp, sp_buthp *p, SPFLOAT *in, SPFLOAT *out);
