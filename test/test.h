typedef struct {
    SPFLOAT *buf;
    uint32_t size;
    uint32_t pos;
    md5_state_t state;
    md5_byte_t digest[16];
    char md5string[33];
    char *md5;
} sp_test;

typedef struct {
    int (* func)(sp_test *, sp_data *, const char*);
    const char *desc;
    const char *hash;
} sp_test_entry;

int sp_test_create(sp_test **t, uint32_t bufsize);
int sp_test_destroy(sp_test **t);
int sp_test_add_sample(sp_test *t, SPFLOAT sample);
int sp_test_compare(sp_test *t, const char *md5hash);
int sp_test_write_raw(sp_test *t, uint32_t index);
