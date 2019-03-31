typedef struct {
    SPFLOAT bar;
} sp_granule;

int sp_granule_create(sp_granule **p);
int sp_granule_destroy(sp_granule **p);
int sp_granule_init(sp_data *sp, sp_granule *p);
int sp_granule_compute(sp_data *sp, sp_granule *p, SPFLOAT *in, SPFLOAT *out);
