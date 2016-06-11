typedef struct {
    SPFLOAT bar;
} sp_hilbert;

int sp_hilbert_create(sp_hilbert **p);
int sp_hilbert_destroy(sp_hilbert **p);
int sp_hilbert_init(sp_data *sp, sp_hilbert *p);
int sp_hilbert_compute(sp_data *sp, sp_hilbert *p, SPFLOAT *in, SPFLOAT *out);
