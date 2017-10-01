
#ifndef SP_TALKBOX_BUFMAX
#define SP_TALKBOX_BUFMAX 1600
#endif

typedef struct {
    SPFLOAT quality;
    SPFLOAT d0, d1, d2, d3, d4;
    SPFLOAT u0, u1, u2, u3, u4;
    SPFLOAT FX;
    SPFLOAT emphasis;
    SPFLOAT car0[SP_TALKBOX_BUFMAX]; 
    SPFLOAT car1[SP_TALKBOX_BUFMAX];
    SPFLOAT window[SP_TALKBOX_BUFMAX];
    SPFLOAT buf0[SP_TALKBOX_BUFMAX];
    SPFLOAT buf1[SP_TALKBOX_BUFMAX];
    uint32_t K, N, O, pos;
} sp_talkbox;

int sp_talkbox_create(sp_talkbox **p);
int sp_talkbox_destroy(sp_talkbox **p);
int sp_talkbox_init(sp_data *sp, sp_talkbox *p);
int sp_talkbox_compute(sp_data *sp, sp_talkbox *p, SPFLOAT *src, SPFLOAT *exc, SPFLOAT *out);
