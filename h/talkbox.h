typedef struct {
    SPFLOAT bar;
} sp_talkbox;

int sp_talkbox_create(sp_talkbox **p);
int sp_talkbox_destroy(sp_talkbox **p);
int sp_talkbox_init(sp_data *sp, sp_talkbox *p);
int sp_talkbox_compute(sp_data *sp, sp_talkbox *p, SPFLOAT *in, SPFLOAT *out);
