typedef struct {
    SPFLOAT min, max, cps_min, cps_max;
    SPFLOAT si;
    SPFLOAT phs;
    int rmin_cod, rmax_cod;
    SPFLOAT num0, num1, num2, df0, df1, c3, c2;
    SPFLOAT onedsr;
    int holdrand;
    int init;
} sp_rspline;

int sp_rspline_create(sp_rspline **p);
int sp_rspline_destroy(sp_rspline **p);
int sp_rspline_init(sp_data *sp, sp_rspline *p);
int sp_rspline_compute(sp_data *sp, sp_rspline *p, SPFLOAT *in, SPFLOAT *out);
