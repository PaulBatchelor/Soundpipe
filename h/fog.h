typedef struct {
    SPFLOAT bar;
} sp_fog;

int sp_fog_create(sp_fog **p);
int sp_fog_destroy(sp_fog **p);
int sp_fog_init(sp_data *sp, sp_fog *p);
int sp_fog_compute(sp_data *sp, sp_fog *p, SPFLOAT *in, SPFLOAT *out);
