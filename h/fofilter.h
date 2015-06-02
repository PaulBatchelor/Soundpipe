typedef struct{
    SPFLOAT freq, ris, dec, istor;
    SPFLOAT tpidsr;
    SPFLOAT sr;
    SPFLOAT delay[4];
}sp_fofilter;

int sp_fofilter_create(sp_fofilter **t);
int sp_fofilter_destroy(sp_fofilter **t);
int sp_fofilter_init(sp_data *sp, sp_fofilter *p);
int sp_fofilter_compute(sp_data *sp, sp_fofilter *p, SPFLOAT *in, SPFLOAT *out);

