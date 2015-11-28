typedef struct {
    SPFLOAT bar;
} sp_randh;

int sp_randh_create(sp_randh **p);
int sp_randh_destroy(sp_randh **p);
int sp_randh_init(sp_data *sp, sp_randh *p);
int sp_randh_compute(sp_data *sp, sp_randh *p, SPFLOAT *in, SPFLOAT *out);
