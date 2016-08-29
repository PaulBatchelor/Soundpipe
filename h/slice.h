typedef struct {
    SPFLOAT bar;
} sp_slice;

int sp_slice_create(sp_slice **p);
int sp_slice_destroy(sp_slice **p);
int sp_slice_init(sp_data *sp, sp_slice *p);
int sp_slice_compute(sp_data *sp, sp_slice *p, SPFLOAT *in, SPFLOAT *out);
