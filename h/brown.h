typedef struct {
    SPFLOAT brown;
} sp_brown;

int sp_brown_create(sp_brown **p);
int sp_brown_destroy(sp_brown **p);
int sp_brown_init(sp_data *sp, sp_brown *p);
int sp_brown_compute(sp_data *sp, sp_brown *p, SPFLOAT *in, SPFLOAT *out);
