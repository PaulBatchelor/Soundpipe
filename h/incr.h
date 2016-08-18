typedef struct {
    SPFLOAT incr;
    SPFLOAT min;
    SPFLOAT max;
    SPFLOAT val;
    char init;
} sp_incr;

int sp_incr_create(sp_incr **p);
int sp_incr_destroy(sp_incr **p);
int sp_incr_init(sp_data *sp, sp_incr *p);
int sp_incr_compute(sp_data *sp, sp_incr *p, SPFLOAT *in, SPFLOAT *out);
