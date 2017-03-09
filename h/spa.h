typedef struct {
    SPFLOAT *buf;
    uint32_t pos;
    sp_audio spa;
} sp_spa;

int sp_spa_create(sp_spa **p);
int sp_spa_destroy(sp_spa **p);
int sp_spa_init(sp_data *sp, sp_spa *p, const char *filename);
int sp_spa_compute(sp_data *sp, sp_spa *p, SPFLOAT *in, SPFLOAT *out);
