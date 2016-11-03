typedef struct
{
    SPFLOAT drive;
    SPFLOAT dcoffset;

    SPFLOAT dcblocker[2][7];

    SPFLOAT ai[6][7];
    SPFLOAT aa[6][7];
} sp_saturator;

int sp_saturator_create(sp_saturator **p);
int sp_saturator_destroy(sp_saturator **p);
int sp_saturator_init(sp_data *sp, sp_saturator *p);
int sp_saturator_compute(sp_data *sp, sp_saturator *p, SPFLOAT *in, SPFLOAT *out);
