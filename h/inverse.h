typedef struct {
    char empty; /* To prevent warnings about C/C++ empty structs */
} sp_inverse;

int sp_inverse_create(sp_inverse **p);
int sp_inverse_destroy(sp_inverse **p);
int sp_inverse_init(sp_data *sp, sp_inverse *p);
int sp_inverse_compute(sp_data *sp, sp_inverse *p, SPFLOAT *in, SPFLOAT *out);
