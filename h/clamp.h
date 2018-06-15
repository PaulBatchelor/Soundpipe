typedef struct {
    SPFLOAT min;
    SPFLOAT max;
} sp_clamp;

int sp_clamp_create(sp_clamp **p);
int sp_clamp_destroy(sp_clamp **p);
int sp_clamp_init(sp_data *sp, sp_clamp *p);
int sp_clamp_compute(sp_data *sp, sp_clamp *p, SPFLOAT *in, SPFLOAT *out);
