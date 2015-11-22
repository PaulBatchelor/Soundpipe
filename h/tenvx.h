typedef struct sp_tenvx{
    sp_tevent *te;
    uint32_t pos, atk_end, rel_start, sr, totaldur;
    SPFLOAT atk, rel, hold;
    SPFLOAT atk_slp, rel_slp;
    SPFLOAT last;
    int sigmode;
    SPFLOAT input;
} sp_tenvx;

int sp_tenvx_create(sp_tenvx **p);
int sp_tenvx_destroy(sp_tenvx **p);
int sp_tenvx_init(sp_data *sp, sp_tenvx *p);
int sp_tenvx_compute(sp_data *sp, sp_tenvx *p, SPFLOAT *in, SPFLOAT *out);
