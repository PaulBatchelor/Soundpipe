typedef struct {
    char empty; /* To prevent warnings about C/C++ empty structs */
} sp_add;

int sp_add_create(sp_add **p);
int sp_add_destroy(sp_add **p);
int sp_add_init(sp_data *sp, sp_add *p);
int sp_add_compute(sp_data *sp, sp_add *p, SPFLOAT *in1, SPFLOAT *in2, SPFLOAT *out);
