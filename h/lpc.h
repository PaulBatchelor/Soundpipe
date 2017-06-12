typedef struct {
    struct openlpc_e_state *e;
    struct openlpc_d_state *d;
    int counter;
    short *in;
    short *out;
    unsigned char data[7];
    SPFLOAT samp;
    unsigned int clock;
    unsigned int block;
    int framesize;
    sp_auxdata m_in;
    sp_auxdata m_out;
    sp_auxdata m_e;
    sp_auxdata m_d;
} sp_lpc;

int sp_lpc_create(sp_lpc **lpc);
int sp_lpc_destroy(sp_lpc **lpc);
int sp_lpc_init(sp_data *sp, sp_lpc *lpc, int framesize);
int sp_lpc_compute(sp_data *sp, sp_lpc *lpc, SPFLOAT *in, SPFLOAT *out);
