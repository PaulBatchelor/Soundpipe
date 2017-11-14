typedef struct {
    SPFLOAT bar;
} sp_wavin;

int sp_wavin_create(sp_wavin **p);
int sp_wavin_destroy(sp_wavin **p);
int sp_wavin_init(sp_data *sp, sp_wavin *p);
int sp_wavin_compute(sp_data *sp, sp_wavin *p, SPFLOAT *in, SPFLOAT *out);
