typedef struct {
    SPFLOAT bar;
} sp_oscmorph;

int sp_oscmorph_create(sp_oscmorph **p);
int sp_oscmorph_destroy(sp_oscmorph **p);
int sp_oscmorph_init(sp_data *sp, sp_oscmorph *p);
int sp_oscmorph_compute(sp_data *sp, sp_oscmorph *p, SPFLOAT *in, SPFLOAT *out);
