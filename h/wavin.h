typedef struct sp_wavin sp_wavin;
int sp_wavin_create(sp_wavin **p);
int sp_wavin_destroy(sp_wavin **p);
int sp_wavin_init(sp_data *sp, sp_wavin *p, const char *filename);
int sp_wavin_compute(sp_data *sp, sp_wavin *p, SPFLOAT *in, SPFLOAT *out);
int sp_wavin_get_sample(sp_data *sp, sp_wavin *p, SPFLOAT *out, SPFLOAT pos);
int sp_wavin_reset_to_start(sp_data *sp, sp_wavin *p);
int sp_wavin_seek(sp_data *sp, sp_wavin *p, unsigned long sample);
