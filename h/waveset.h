typedef struct {
    SPFLOAT bar;
} sp_waveset;

int sp_waveset_create(sp_waveset **p);
int sp_waveset_destroy(sp_waveset **p);
int sp_waveset_init(sp_data *sp, sp_waveset *p);
int sp_waveset_compute(sp_data *sp, sp_waveset *p, SPFLOAT *in, SPFLOAT *out);
