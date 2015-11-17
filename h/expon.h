typedef struct {
    SPFLOAT ia, idur, ib;
    SPFLOAT val, incr; 
    uint32_t sdur, stime;
} sp_expon;

int sp_expon_create(sp_expon **p);
int sp_expon_destroy(sp_expon **p);
int sp_expon_init(sp_data *sp, sp_expon *p, SPFLOAT ia, SPFLOAT idur, SPFLOAT ib);
int sp_expon_compute(sp_data *sp, sp_expon *p, SPFLOAT *in, SPFLOAT *out);
