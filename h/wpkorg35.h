typedef struct {
    SPFLOAT m_fSampleRate;
    SPFLOAT m_fFc;
    uint32_t m_uFilterType;
    SPFLOAT m_fAlpha;
    SPFLOAT m_fBeta;
} sp_va_onepole;

typedef struct {
    //sp_va_onepole m_LPF1;
    //sp_va_onepole m_LPF2;
    //sp_va_onepole m_HPF1;

    /* LPF1 */
    SPFLOAT lpf1_fc;
    SPFLOAT lpf1_a;
    SPFLOAT lpf1_b;
    SPFLOAT lpf1_z;
    
    /* LPF2 */
    SPFLOAT lpf2_fc;
    SPFLOAT lpf2_a;
    SPFLOAT lpf2_b;
    SPFLOAT lpf2_z;
    
    /* HPF */
    SPFLOAT hpf_fc;
    SPFLOAT hpf_a;
    SPFLOAT hpf_b;
    SPFLOAT hpf_z;

    SPFLOAT m_dAlpha0;
    SPFLOAT m_nSampleRate;
    SPFLOAT m_dFC;
    SPFLOAT m_dK;
    SPFLOAT m_dSaturation;
    uint32_t m_uNonLinearProcessing;
} sp_wpkorg35;

int sp_wpkorg35_create(sp_wpkorg35 **p);
int sp_wpkorg35_destroy(sp_wpkorg35 **p);
int sp_wpkorg35_init(sp_data *sp, sp_wpkorg35 *p);
int sp_wpkorg35_compute(sp_data *sp, sp_wpkorg35 *p, SPFLOAT *in, SPFLOAT *out);
