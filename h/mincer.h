typedef struct {
    SPFLOAT bar;
} sp_mincer;

int sp_mincer_create(sp_mincer **p);
int sp_mincer_destroy(sp_mincer **p);
int sp_mincer_init(sp_data *sp, sp_mincer *p);
int sp_mincer_compute(sp_data *sp, sp_mincer *p, SPFLOAT *in, SPFLOAT *out);
