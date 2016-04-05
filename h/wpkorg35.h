typedef struct {
    SPFLOAT bar;
} sp_wpkorg35;

int sp_wpkorg35_create(sp_wpkorg35 **p);
int sp_wpkorg35_destroy(sp_wpkorg35 **p);
int sp_wpkorg35_init(sp_data *sp, sp_wpkorg35 *p);
int sp_wpkorg35_compute(sp_data *sp, sp_wpkorg35 *p, SPFLOAT *in, SPFLOAT *out);
