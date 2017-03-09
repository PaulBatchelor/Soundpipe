typedef struct {
    SPFLOAT bar;
} sp_sparec;

int sp_sparec_create(sp_sparec **p);
int sp_sparec_destroy(sp_sparec **p);
int sp_sparec_init(sp_data *sp, sp_sparec *p);
int sp_sparec_compute(sp_data *sp, sp_sparec *p, SPFLOAT *in, SPFLOAT *out);
