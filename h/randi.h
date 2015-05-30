#define sp_oneUp31Bit      (4.656612875245796924105750827168e-10)

#define sp_randGab   ((SPFLOAT)     \
        (((p->holdrand = p->holdrand * 214013 + 2531011) >> 1)  \
         & 0x7fffffff) * sp_oneUp31Bit)

typedef struct {
    SPFLOAT min, max, cps, mode, fstval;
    int16_t cpscod;
    int32_t phs;
    SPFLOAT num1, num2, dfdmax;
    int holdrand;
    SPFLOAT sicvt;
} sp_randi;

int sp_randi_create(sp_randi **p);
int sp_randi_destroy(sp_randi **p);
int sp_randi_init(sp_data *sp, sp_randi *p, int seed);
int sp_randi_compute(sp_data *sp, sp_randi *p, SPFLOAT *in, SPFLOAT *out);
