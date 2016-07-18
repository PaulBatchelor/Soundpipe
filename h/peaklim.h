typedef struct {
    SPFLOAT bar;
} sp_peaklim;

int sp_peaklim_create(sp_peaklim **p);
int sp_peaklim_destroy(sp_peaklim **p);
int sp_peaklim_init(sp_data *sp, sp_peaklim *p);
int sp_peaklim_compute(sp_data *sp, sp_peaklim *p, SPFLOAT *in, SPFLOAT *out);
