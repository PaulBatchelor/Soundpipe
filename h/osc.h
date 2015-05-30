typedef struct {
    SPFLOAT freq, amp;
    sp_ftbl *tbl;
} sp_osc;

int sp_osc_create(sp_tone **t);
int sp_osc_destroy(sp_tone **t);
int sp_osc_init(sp_data *sp, sp_tone *t, sp_ftbl *ft);
int sp_osc_compute(sp_data *sp, sp_tone *t, SPFLOAT *in, SPFLOAT *out);
