typedef struct sp_ftbl{
    size_t size;
    SPFLOAT *tbl;
}sp_ftbl;

int sp_ftbl_create(sp_ftbl **ft, size_t size);
int sp_ftbl_destroy(sp_ftbl **ft);
int sp_gen_sine(sp_ftbl *ft);
