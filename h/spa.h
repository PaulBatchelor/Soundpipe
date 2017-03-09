typedef struct {
    SPFLOAT *buf;
    uint32_t pos;
    uint32_t bufsize;
    sp_audio spa;
    sp_auxdata aux;
} sp_spa;

int sp_spa_create(sp_spa **p);
int sp_spa_destroy(sp_spa **p);
int sp_spa_init(sp_data *sp, sp_spa *p, const char *filename);
int sp_spa_compute(sp_data *sp, sp_spa *p, SPFLOAT *in, SPFLOAT *out);
