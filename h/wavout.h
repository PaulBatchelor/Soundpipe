typedef struct sp_wavout sp_wavout;
int sp_wavout_create(sp_wavout **p);
int sp_wavout_destroy(sp_wavout **p);
int sp_wavout_init(sp_data *sp, sp_wavout *p, const char *filename);
int sp_wavout_compute(sp_data *sp, sp_wavout *p, SPFLOAT *in, SPFLOAT *out);
