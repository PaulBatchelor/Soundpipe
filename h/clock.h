typedef struct {
    SPFLOAT bpm;
    SPFLOAT subdiv;
    uint32_t counter;
} sp_clock;

int sp_clock_create(sp_clock **p);
int sp_clock_destroy(sp_clock **p);
int sp_clock_init(sp_data *sp, sp_clock *p);
int sp_clock_compute(sp_data *sp, sp_clock *p, SPFLOAT *trig, SPFLOAT *out);
