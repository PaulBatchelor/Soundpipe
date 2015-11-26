typedef struct {
    void *ud;
    int argpos;
    SPFLOAT *args[2];
    SPFLOAT *freq;
    SPFLOAT *amp;
} sp_triangle;

int sp_triangle_create(sp_triangle **p);
int sp_triangle_destroy(sp_triangle **p);
int sp_triangle_init(sp_data *sp, sp_triangle *p);
int sp_triangle_compute(sp_data *sp, sp_triangle *p, SPFLOAT *in, SPFLOAT *out);

