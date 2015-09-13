typedef struct {
    SPFLOAT bit;
    SPFLOAT srate;
    sp_fold *fold;
} sp_decimator;

int sp_decimator_create(sp_decimator **p);
int sp_decimator_destroy(sp_decimator **p);
int sp_decimator_init(sp_data *sp, sp_decimator *p);
int sp_decimator_compute(sp_data *sp, sp_decimator *p, SPFLOAT *in, SPFLOAT *out);
