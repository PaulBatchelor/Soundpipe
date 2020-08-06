typedef struct{
    SPFLOAT smooth;
    SPFLOAT a1, b0, y0, psmooth;
    SPFLOAT onedsr;
}sp_port;

int sp_port_create(sp_port **p);
int sp_port_destroy(sp_port **p);
int sp_port_init(sp_data *sp, sp_port *p);
int sp_port_compute(sp_data *sp, sp_port *p, SPFLOAT *in, SPFLOAT *out);
int sp_port_reset(sp_data *sp, sp_port *p, SPFLOAT *in);
