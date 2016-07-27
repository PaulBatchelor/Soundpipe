typedef struct {
    SPFLOAT bar;
} sp_smoothdelay;

int sp_smoothdelay_create(sp_smoothdelay **p);
int sp_smoothdelay_destroy(sp_smoothdelay **p);
int sp_smoothdelay_init(sp_data *sp, sp_smoothdelay *p);
int sp_smoothdelay_compute(sp_data *sp, sp_smoothdelay *p, SPFLOAT *in, SPFLOAT *out);
