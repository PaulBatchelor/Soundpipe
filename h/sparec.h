typedef struct {
    SPFLOAT *buf;
    uint32_t pos;
    uint32_t bufsize;
    sp_audio spa;
    sp_auxdata aux;
} sp_sparec;

int sp_sparec_create(sp_sparec **p);
int sp_sparec_destroy(sp_sparec **p);
int sp_sparec_init(sp_data *sp, sp_sparec *p, const char *filename);
int sp_sparec_compute(sp_data *sp, sp_sparec *p, SPFLOAT *in, SPFLOAT *out);
int sp_sparec_close(sp_data *sp, sp_sparec *p);
