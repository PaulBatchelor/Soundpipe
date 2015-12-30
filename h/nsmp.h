typedef struct nano_entry {
    char name[50];
    uint32_t pos;
    uint32_t size;
    struct nano_entry *next;
} nano_entry;

typedef struct {
    int nval;
    int init;
    nano_entry root;
    nano_entry *last;
} nano_dict;

typedef struct {
    char ini[100];
    char wav[100];
    SPFLOAT curpos;
    nano_dict dict;
    int selected;
    nano_entry *sample;
    nano_entry **index; 
/*
    SNDFILE *sndfile;
    SF_INFO info;
*/
    sp_ftbl *ft;
    int sr;
    sp_tabread *tr;
} nanosamp;

typedef struct {
    nanosamp *smp;
    uint32_t index;
    int triggered;
} sp_nsmp;

/*
int nano_create(nanosamp **smp, const char *wav, const char *ini);
int nano_select(nanosamp *smp, const char *keyword);
int nano_ini_handler(void *user, const char *section, const char *name,
        const char *value);
int nano_dict_add(nano_dict *dict, const char *name);
int nano_dict_destroy(nano_dict *dict);
int nano_compute(nanosamp *smp, float *out);
int nano_destroy(nanosamp **smp);

int nano_create_index(nanosamp *smp);
uint32_t nano_keyword_to_index(nanosamp *smp, const char *keyword);
int nano_select_from_index(nanosamp *smp, uint32_t pos);
int nano_destroy_index(nanosamp *smp);
*/

int sp_nsmp_create(sp_nsmp **p);
int sp_nsmp_destroy(sp_nsmp **p);
int sp_nsmp_init(sp_data *sp, sp_nsmp *p, sp_ftbl *ft, int sr, const char *ini);
int sp_nsmp_compute(sp_data *sp, sp_nsmp *p, SPFLOAT *in, SPFLOAT *out);

int sp_nsmp_print_index(sp_data *sp, sp_nsmp *p);
