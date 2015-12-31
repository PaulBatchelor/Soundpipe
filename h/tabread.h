typedef struct {
    SPFLOAT sig;
    SPFLOAT index, mode, offset, wrap;
    SPFLOAT mul;
    int32_t np2;
    int32_t len;
    int32_t lenmask;
    sp_ftbl *ft;
} sp_tabread;

int sp_tabread_create(sp_tabread **p);
int sp_tabread_destroy(sp_tabread **p);
int sp_tabread_init(sp_data *sp, sp_tabread *p, sp_ftbl *ft);
int sp_tabread_compute(sp_data *sp, sp_tabread *p, SPFLOAT *in, SPFLOAT *out);
