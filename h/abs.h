typedef struct {
    char empty; /* Dummy variable to prevent compilation warnings about C/C++ empty structs */
} sp_abs;

int sp_abs_create(sp_abs **p);
int sp_abs_destroy(sp_abs **p);
int sp_abs_init(sp_data *sp, sp_abs *p);
int sp_abs_compute(sp_data *sp, sp_abs *p, SPFLOAT *in, SPFLOAT *out);
