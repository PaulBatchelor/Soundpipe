typedef struct {
    SPFLOAT bar;
} sp_fof;

int sp_fof_create(sp_fof **p);
int sp_fof_destroy(sp_fof **p);
int sp_fof_init(sp_data *sp, sp_fof *p);
int sp_fof_compute(sp_data *sp, sp_fof *p, SPFLOAT *in, SPFLOAT *out);
