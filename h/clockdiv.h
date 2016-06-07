typedef struct {
    SPFLOAT bar;
} sp_clockdiv;

int sp_clockdiv_create(sp_clockdiv **p);
int sp_clockdiv_destroy(sp_clockdiv **p);
int sp_clockdiv_init(sp_data *sp, sp_clockdiv *p);
int sp_clockdiv_compute(sp_data *sp, sp_clockdiv *p, SPFLOAT *in, SPFLOAT *out);
