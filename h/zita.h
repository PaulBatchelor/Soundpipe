typedef struct {
    void *ud;
    SPFLOAT *args[11];
    int argpos;
    SPFLOAT *in_delay;
    SPFLOAT *lf_x;
    SPFLOAT *rt60_low;
    SPFLOAT *rt60_mid;
    SPFLOAT *hf_damping;
    SPFLOAT *eq1_freq;
    SPFLOAT *eq1_level;
    SPFLOAT *eq2_freq;
    SPFLOAT *eq2_level;
    SPFLOAT *mix;
    SPFLOAT *level;
} sp_zita;

int sp_zita_create(sp_zita **p);
int sp_zita_destroy(sp_zita **p);
int sp_zita_init(sp_data *sp, sp_zita *p);
int sp_zita_compute(sp_data *sp, sp_zita *p, SPFLOAT *inL, SPFLOAT *inR, SPFLOAT *outL, SPFLOAT *outR);
