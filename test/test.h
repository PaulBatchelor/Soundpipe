typedef struct {
    SPFLOAT *buf;
    uint32_t size;
    uint32_t pos;
    md5_state_t state;
    md5_byte_t digest[16];
    char md5string[33];
} sp_test;

int sp_test_create(sp_test **t, uint32_t bufsize);
int sp_test_destroy(sp_test **t);
int sp_test_add_sample(sp_test *t, SPFLOAT sample);
int sp_test_compare(sp_test *t, const char *md5hash);
