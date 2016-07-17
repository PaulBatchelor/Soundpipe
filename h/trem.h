typedef struct {
    SPFLOAT freq, iphs;
    sp_ftbl *tbl;
    int32_t lphs;
    int inc;
} sp_trem;

int sp_trem_create(sp_trem **trem);
int sp_trem_destroy(sp_trem **trem);
int sp_trem_init(sp_data *sp, sp_trem *trem, sp_ftbl *ft);
int sp_trem_compute(sp_data *sp, sp_trem *trem, SPFLOAT *in, SPFLOAT *out);
