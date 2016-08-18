typedef struct prop_event {
    char type;
    uint32_t pos;
    uint32_t val;
    uint32_t cons;
    struct prop_event *next;
} prop_event;

typedef struct {
    uint32_t stack[16];
    int pos;
} prop_stack;

typedef struct {
    uint32_t mul;
    uint32_t div;
    uint32_t tmp;
    uint32_t num;
    uint32_t cons_mul;
    uint32_t cons_div;
    SPFLOAT scale;
    int mode;
    uint32_t pos;
    uint32_t evtpos;
    prop_event root;
    prop_event *main;
    prop_event *last;
    prop_stack mstack;
    prop_stack cstack;
} prop_data;

typedef struct {
   prop_data *prp;
   prop_event evt;
   uint32_t count;
   SPFLOAT bpm;
   SPFLOAT lbpm;
} sp_prop;

int sp_prop_create(sp_prop **p);
int sp_prop_destroy(sp_prop **p);
int sp_prop_init(sp_data *sp, sp_prop *p, const char *str);
int sp_prop_compute(sp_data *sp, sp_prop *p, SPFLOAT *in, SPFLOAT *out);
