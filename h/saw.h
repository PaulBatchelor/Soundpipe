typedef struct {
    void *ud;
    int argpos;
    SPFLOAT *args[2];
    SPFLOAT *freq;
    SPFLOAT *amp;
} sp_saw;

int sp_saw_create(sp_saw **p);
int sp_saw_destroy(sp_saw **p);
int sp_saw_init(sp_data *sp, sp_saw *p);
int sp_saw_compute(sp_data *sp, sp_saw *p, SPFLOAT *in, SPFLOAT *out);
