typedef struct {
    SPFLOAT freq, amp, iphs;
    int32_t   lphs;
    sp_ftbl *tbl;
} sp_osc;

int sp_osc_create(sp_osc **osc);
int sp_osc_destroy(sp_osc **osc);
int sp_osc_init(sp_data *sp, sp_osc *osc, sp_ftbl *ft);
int sp_osc_compute(sp_data *sp, sp_osc *osc, SPFLOAT *in, SPFLOAT *out);
