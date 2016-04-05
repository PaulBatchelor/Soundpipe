typedef struct {
    SPFLOAT m_fSampleRate;
    SPFLOAT m_fFc;
    uint32_t m_uFilterType;
    SPFLOAT m_fAlpha;
    SPFLOAT m_fBeta;
} sp_va_onepole;

typedef struct {
    sp_va_onepole m_LPF1;
    sp_va_onepole m_LPF2;
    sp_va_onepole m_HPF1;

} sp_wpkorg35;

int sp_wpkorg35_create(sp_wpkorg35 **p);
int sp_wpkorg35_destroy(sp_wpkorg35 **p);
int sp_wpkorg35_init(sp_data *sp, sp_wpkorg35 *p);
int sp_wpkorg35_compute(sp_data *sp, sp_wpkorg35 *p, SPFLOAT *in, SPFLOAT *out);
