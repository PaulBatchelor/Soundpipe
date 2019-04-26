typedef struct sp_wavin sp_wavin;
int sp_wavin_create(sp_wavin **p);
int sp_wavin_destroy(sp_wavin **p);
int sp_wavin_init(sp_wavin *p, const char *filename);
int sp_wavin_compute(sp_wavin *p, SPFLOAT *out);
int sp_wavin_getSample(sp_wavin *p, SPFLOAT *out, float position);
int sp_wavin_resetToStart(sp_wavin *p);
int sp_wavin_seek(sp_wavin *p, unsigned long sample);
