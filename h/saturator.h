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

    SPFLOAT dcBlocker[2][7];

		SPFLOAT AIFilter[kAAOrder][7];
		SPFLOAT AAFilter[kAAOrder][7];
} sp_saturator;

int sp_saturator_create(sp_saturator **p);
int sp_saturator_destroy(sp_saturator **p);
int sp_saturator_init(sp_data *sp, sp_saturator *p);
int sp_saturator_compute(sp_data *sp, sp_saturator *p, SPFLOAT *in, SPFLOAT *out);
