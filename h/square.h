typedef struct {
    void *ud;
    int argpos;
    SPFLOAT *args[3];
    SPFLOAT *freq;
    SPFLOAT *amp;
    SPFLOAT *width;
} sp_square;

int sp_square_create(sp_square **p);
int sp_square_destroy(sp_square **p);
int sp_square_init(sp_data *sp, sp_square *p);
int sp_square_compute(sp_data *sp, sp_square *p, SPFLOAT *in, SPFLOAT *out);
