typedef struct {
    char empty; /* To prevent warnings about C/C++ empty structs */
} sp_sub;

int sp_sub_create(sp_sub **p);
int sp_sub_destroy(sp_sub **p);
int sp_sub_init(sp_data *sp, sp_sub *p);
int sp_sub_compute(sp_data *sp, sp_sub *p, SPFLOAT *in1, SPFLOAT *in2, SPFLOAT *out);
