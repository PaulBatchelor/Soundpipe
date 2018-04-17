typedef struct sp_wavin sp_wavin;
int sp_wavin_create(sp_wavin **p);
int sp_wavin_destroy(sp_wavin **p);
int sp_wavin_init(sp_data *sp, sp_wavin *p, const char *filename);
int sp_wavin_compute(sp_data *sp, sp_wavin *p, SPFLOAT *in, SPFLOAT *out);
