typedef struct {
    SPFLOAT bar;
} sp_tadsr;

int sp_tadsr_create(sp_tadsr **p);
int sp_tadsr_destroy(sp_tadsr **p);
int sp_tadsr_init(sp_data *sp, sp_tadsr *p);
int sp_tadsr_compute(sp_data *sp, sp_tadsr *p, SPFLOAT *in, SPFLOAT *out);
