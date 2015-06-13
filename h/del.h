typedef struct sp_del{
    SPFLOAT del, maxdel;
    SPFLOAT sr;
    sp_auxdata buf;
    int32_t left;
} sp_del;

int sp_del_create(sp_del **p);
int sp_del_destroy(sp_del **p);
int sp_del_init(sp_data *sp, sp_del *p, SPFLOAT maxdel);
int sp_del_compute(sp_data *sp, sp_del *p, SPFLOAT *in, SPFLOAT *out);
