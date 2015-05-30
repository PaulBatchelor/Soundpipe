#define SP_FT_MAXLEN 0x1000000L
#define SP_FT_PHMASK 0x0FFFFFFL

typedef struct sp_ftbl{
    size_t size;
    uint32_t lobits;
    uint32_t lomask;
    SPFLOAT lodiv;
    SPFLOAT sicvt;
    SPFLOAT *tbl;
}sp_ftbl;

int sp_ftbl_create(sp_data *sp, sp_ftbl **ft, size_t size);
int sp_ftbl_destroy(sp_ftbl **ft);

int sp_gen_sine(sp_ftbl *ft);
int sp_gen_file(sp_ftbl *ft, const char *filename);
