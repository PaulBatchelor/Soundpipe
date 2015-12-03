typedef typedef struct {
    char emptyStruct;
} sp_div;

int sp_div_create(sp_div **p);
int sp_div_destroy(sp_div **p);
int sp_div_init(sp_data *sp, sp_div *p);
int sp_div_compute(sp_data *sp, sp_div *p, SPFLOAT *in1, SPFLOAT *in2, SPFLOAT *out);
