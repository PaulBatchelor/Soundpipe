typedef struct {
    sp_ftbl *ft;
    SPFLOAT speed;  
    SPFLOAT pos;
} sp_tabread;

int sp_tabread_create(sp_tabread **p);
int sp_tabread_destroy(sp_tabread **p);
int sp_tabread_init(sp_data *sp, sp_tabread *p, sp_ftbl *ft);
int sp_tabread_compute(sp_data *sp, sp_tabread *p, SPFLOAT *in, SPFLOAT *out);
