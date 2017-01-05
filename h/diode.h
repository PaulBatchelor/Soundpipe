typedef struct {
    /* 4 one-pole filters */
    SPFLOAT opva_alpha[4];
    SPFLOAT opva_beta[4];
    SPFLOAT opva_gamma[4];
    SPFLOAT opva_delta[4];
    SPFLOAT opva_eps[4];
    SPFLOAT opva_a0[4];
    SPFLOAT opva_fdbk[4];
    SPFLOAT opva_z1[4];
    /* end one-pole filters */

    SPFLOAT SG[4];
    SPFLOAT gamma;
    SPFLOAT freq;
    SPFLOAT K;
    SPFLOAT res;
} sp_diode;

int sp_diode_create(sp_diode **p);
int sp_diode_destroy(sp_diode **p);
int sp_diode_init(sp_data *sp, sp_diode *p);
int sp_diode_compute(sp_data *sp, sp_diode *p, SPFLOAT *in, SPFLOAT *out);
