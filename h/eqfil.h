typedef struct {
  SPFLOAT freq, bw, gain, ini;
  SPFLOAT z1,z2, sr;
  SPFLOAT frv, bwv;
  double c,d;
} sp_eqfil;

int sp_eqfil_create(sp_eqfil **p);
int sp_eqfil_destroy(sp_eqfil **p);
int sp_eqfil_init(sp_data *sp, sp_eqfil *p, SPFLOAT freq, SPFLOAT bw, SPFLOAT gain);
int sp_eqfil_compute(sp_data *sp, sp_eqfil *p, SPFLOAT *in, SPFLOAT *out);
