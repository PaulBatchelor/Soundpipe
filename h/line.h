typedef struct {
    SPFLOAT ia, idur, ib;
    SPFLOAT val, incr; 
    uint32_t sdur, stime;
} sp_line;

int sp_line_create(sp_line **p);
int sp_line_destroy(sp_line **p);
int sp_line_init(sp_data *sp, sp_line *p, SPFLOAT ia, SPFLOAT idur, SPFLOAT ib);
int sp_line_compute(sp_data *sp, sp_line *p, SPFLOAT *in, SPFLOAT *out);
