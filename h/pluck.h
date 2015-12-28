typedef struct {
    SPFLOAT *ar, *kamp, *kcps, *icps, *ifn, *imeth, *ipar1, *ipar2;
    SPFLOAT sicps, param1, param2;
    int16_t thresh1, thresh2, method;
    int32_t phs256, npts, maxpts;
    sp_auxdata auxch;
} sp_pluck;

int sp_pluck_create(sp_pluck **p);
int sp_pluck_destroy(sp_pluck **p);
int sp_pluck_init(sp_data *sp, sp_pluck *p, SPFLOAT ifreq);
int sp_pluck_compute(sp_data *sp, sp_pluck *p, SPFLOAT *trig, SPFLOAT *in, SPFLOAT *out);
