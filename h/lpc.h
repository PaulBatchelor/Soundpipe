typedef struct {
    SPFLOAT bar;
} sp_lpc;

int sp_lpc_create(sp_lpc **p);
int sp_lpc_destroy(sp_lpc **p);
int sp_lpc_init(sp_data *sp, sp_lpc *p);
int sp_lpc_compute(sp_data *sp, sp_lpc *p, SPFLOAT *in, SPFLOAT *out);
