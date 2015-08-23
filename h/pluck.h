typedef struct {
    SPFLOAT plk, amp, freq, pickup, reflect;
    sp_auxdata upper;
    sp_auxdata lower;
    sp_auxdata up_data;
    sp_auxdata down_data;
    SPFLOAT state;
    int scale;
    int rail_len;
} sp_pluck;

int sp_pluck_create(sp_pluck **p);
int sp_pluck_destroy(sp_pluck **p);
int sp_pluck_init(sp_data *sp, sp_pluck *p);
int sp_pluck_compute(sp_data *sp, sp_pluck *p, SPFLOAT *trig, SPFLOAT *in, SPFLOAT *out);
