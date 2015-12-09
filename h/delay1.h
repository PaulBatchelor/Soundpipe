typedef struct {
    SPFLOAT samp;
} sp_delay1;

int sp_delay1_create(sp_delay1 **p);
int sp_delay1_destroy(sp_delay1 **p);
int sp_delay1_init(sp_data *sp, sp_delay1 *p);
int sp_delay1_compute(sp_data *sp, sp_delay1 *p, SPFLOAT *in, SPFLOAT *out);
