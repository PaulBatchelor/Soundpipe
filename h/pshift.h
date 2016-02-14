typedef struct {
    SPFLOAT bar;
} sp_pshift;

int sp_pshift_create(sp_pshift **p);
int sp_pshift_destroy(sp_pshift **p);
int sp_pshift_init(sp_data *sp, sp_pshift *p);
int sp_pshift_compute(sp_data *sp, sp_pshift *p, SPFLOAT *in, SPFLOAT *out);
