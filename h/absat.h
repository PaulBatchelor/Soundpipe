typedef struct
{
    SPFLOAT drive;
    SPFLOAT dcOffset;

    SPFLOAT inputFilterGain;
    SPFLOAT inputFilterCutoff;
    SPFLOAT inputFilterQ;

    SPFLOAT outputFilterGain;
    SPFLOAT outputFilterCutoff;
    SPFLOAT outputFilterQ;

    sp_abquad *dcBlocker[2];

		enum {kAAOrder = 6, kUSRatio = 8} absat_enum;
  	sp_abquad * AIFilter[kAAOrder];
  	sp_abquad * AAFilter[kAAOrder];
} sp_absat;

int sp_absat_create(sp_absat **p);
int sp_absat_destroy(sp_absat **p);
int sp_absat_init(sp_data *sp, sp_absat *p);
int sp_absat_compute(sp_data *sp, sp_absat *p, SPFLOAT *in, SPFLOAT *out);
