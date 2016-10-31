typedef struct
{
		SPFLOAT b0;
		SPFLOAT b1;
		SPFLOAT b2;
		SPFLOAT a1;
		SPFLOAT a2;
		SPFLOAT z1;
		SPFLOAT z2;
} sp_abquad;

int sp_abquad_create(sp_abquad **p);
int sp_abquad_destroy(sp_abquad **p);
int sp_abquad_init(sp_data *sp, sp_abquad *p);
int sp_abquad_compute(sp_data *sp, sp_abquad *p, SPFLOAT *input, SPFLOAT *out);
int sp_abquad_set(sp_data* sp, sp_abquad* p, const SPFLOAT coefs[5]);
