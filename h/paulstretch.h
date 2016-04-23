typedef struct {
    SPFLOAT bar;
} sp_paulstretch;

int sp_paulstretch_create(sp_paulstretch **p);
int sp_paulstretch_destroy(sp_paulstretch **p);
int sp_paulstretch_init(sp_data *sp, sp_paulstretch *p);
int sp_paulstretch_compute(sp_data *sp, sp_paulstretch *p, SPFLOAT *in, SPFLOAT *out);
