typedef struct sp_metro{
    SPFLOAT freq;
    SPFLOAT phs;
    int init;
    SPFLOAT onedsr;
} sp_metro;

int sp_metro_create(sp_metro **p);
int sp_metro_destroy(sp_metro **p);
int sp_metro_init(sp_data *sp, sp_metro *p);
int sp_metro_compute(sp_data *sp, sp_metro *p, SPFLOAT *in, SPFLOAT *out);
