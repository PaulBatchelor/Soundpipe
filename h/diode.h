typedef struct {
    SPFLOAT bar;
} sp_diode;

int sp_diode_create(sp_diode **p);
int sp_diode_destroy(sp_diode **p);
int sp_diode_init(sp_data *sp, sp_diode *p);
int sp_diode_compute(sp_data *sp, sp_diode *p, SPFLOAT *in, SPFLOAT *out);
