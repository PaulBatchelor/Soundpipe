typedef struct {
    SPFLOAT bar;
} sp_ptrack;

int sp_ptrack_create(sp_ptrack **p);
int sp_ptrack_destroy(sp_ptrack **p);
int sp_ptrack_init(sp_data *sp, sp_ptrack *p);
int sp_ptrack_compute(sp_data *sp, sp_ptrack *p, SPFLOAT *in, SPFLOAT *out);
