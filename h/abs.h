typedef struct {
} sp_abs;

int sp_abs_create(sp_abs **p);
int sp_abs_destroy(sp_abs **p);
int sp_abs_init(sp_data *sp, sp_abs *p);
int sp_abs_compute(sp_data *sp, sp_abs *p, SPFLOAT *in, SPFLOAT *out);
