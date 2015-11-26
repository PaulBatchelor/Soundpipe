typedef struct {
    void *faust;
    int argpos;
    SPFLOAT *args[1];
    SPFLOAT *amp;
} sp_pinknoise;

int sp_pinknoise_create(sp_pinknoise **p);
int sp_pinknoise_destroy(sp_pinknoise **p);
int sp_pinknoise_init(sp_data *sp, sp_pinknoise *p);
int sp_pinknoise_compute(sp_data *sp, sp_pinknoise *p, SPFLOAT *in, SPFLOAT *out);

