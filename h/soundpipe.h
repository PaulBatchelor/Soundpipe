#include <sndfile.h>
#include <stdint.h>
#define SP_BUFSIZE 4096
#define SPFLOAT float
#define SP_OK 1
#define SP_NOT_OK 0

#ifndef __SOUNDPIPE_H__
#define __SOUNDPIPE_H__
#endif

typedef unsigned long sp_frame;

typedef struct sp_auxdata{
    size_t size;
    void *ptr;
}sp_auxdata;

typedef struct sp_data{ 
    SPFLOAT buf[SP_BUFSIZE];
    SPFLOAT out;
    SNDFILE *sf;
    int sr;
    unsigned long len;
    unsigned long pos;
    char filename[200];
}sp_data; 

int sp_auxdata_alloc(sp_auxdata *aux, size_t size);
int sp_auxdata_free(sp_auxdata *aux);

int sp_create(sp_data **spp);
int sp_destroy(sp_data **spp);
int sp_process(sp_data *sp, void *ud, void (*callback)(sp_data *, void *));
enum{
SPEVT_FREE,
SPEVT_QUEUED,
SPEVT_ON,
SPEVT_OFF,
SPEVT_ERROR,
SPEVT_ONESAMP
};

enum{
SPEVSTK_SEARCH = -2,
SPEVSTK_NOFREE
};

typedef struct {
    int mode;
    sp_frame start;
    sp_frame end;
    void (*init_cb)(void *);
    void (*evton_cb)(void *);
    void (*evtoff_cb)(void *);
    void *ud;
}sp_event; 

typedef struct {
    sp_event *evt;
    int nevents;
    size_t ud_size;
    int nxtfree;
    int curfree;
    int lstfree;
    int nalloc;
    void (*init_cb)(void *);
    void (*evton_cb)(void *);
    void (*evtoff_cb)(void *);
    void *ud;
    int *t;
}sp_evtstack; 

int sp_event_create(sp_event **evt, int nevents);
int sp_event_init(sp_event *evt);
int sp_event_destroy(sp_event **evt);
/* poorly named function because create implies memory mgt. change. */
int sp_event_insert(sp_event *evt, 
        sp_frame cpos, sp_frame start, sp_frame dur,
        void(*init_cb)(void *),
        void(*evton_cb)(void *),
        void(*evtoff_cb)(void *),
        void *ud); 
int sp_event_clear(sp_event *evt);
int sp_event_update(sp_event *evt, sp_frame pos);
int sp_event_exec(sp_event *evt);

/* event stack functions */

int sp_evtstack_create(sp_evtstack **es, int nevents);
int sp_evtstack_init(sp_evtstack *es, 
        void(*init_cb)(void *),
        void(*evton_cb)(void *),
        void(*evtoff_cb)(void *), 
        void *ud, size_t ud_size);
int sp_evtstack_destroy(sp_evtstack **es);

int sp_evtstack_add(sp_evtstack *es, 
        sp_frame cpos, sp_frame start, sp_frame dur, int *pos);

int sp_evtstack_nextfree(sp_evtstack *es, int *id);

int sp_evtstack_update(sp_evtstack *es, sp_frame pos);
int sp_evtstack_exec(sp_evtstack *es);
int sp_evtstack_full(sp_evtstack *es);
typedef struct{
    SPFLOAT gain;
}sp_noise;

int sp_noise_create(sp_noise **ns);
int sp_noise_init(sp_data *sp, sp_noise *ns);
int sp_noise_compute(sp_data *sp, sp_noise *ns, SPFLOAT *in, SPFLOAT *out);
int sp_noise_destroy(sp_noise **ns);
typedef struct {
        SPFLOAT khp, istor;
        SPFLOAT c1, c2, yt1, prvhp;
        SPFLOAT tpidsr;
} sp_tone;

int sp_tone_create(sp_tone **t);
int sp_tone_destroy(sp_tone **t);
int sp_tone_init(sp_data *sp, sp_tone *t);
int sp_tone_compute(sp_data *sp, sp_tone *t, SPFLOAT *in, SPFLOAT *out);
typedef struct {
    SPFLOAT   freq;
    SPFLOAT   res;
    SPFLOAT   istor;

    SPFLOAT  delay[6];
    SPFLOAT  tanhstg[3];
    SPFLOAT   oldfreq;
    SPFLOAT   oldres;
    SPFLOAT  oldacr;
    SPFLOAT  oldtune;
} sp_moogladder;

int sp_moogladder_create(sp_moogladder **t);
int sp_moogladder_destroy(sp_moogladder **t);
int sp_moogladder_init(sp_data *sp, sp_moogladder *p);
int sp_moogladder_compute(sp_data *sp, sp_moogladder *p, SPFLOAT *in, SPFLOAT *out);
typedef struct  {
    SPFLOAT sr, kfc, istor;
    SPFLOAT lkf;
    SPFLOAT a[8];
    SPFLOAT pidsr;
} sp_butlp;

typedef struct  {
    SPFLOAT sr, kfc, istor;
    SPFLOAT lkf;
    SPFLOAT a[8];
    SPFLOAT pidsr;
} sp_buthp;

int sp_butlp_create(sp_butlp **p);
int sp_butlp_destroy(sp_butlp **p);
int sp_butlp_init(sp_data *sp, sp_butlp *p);
int sp_butlp_compute(sp_data *sp, sp_butlp *p, SPFLOAT *in, SPFLOAT *out);

int sp_buthp_create(sp_buthp **p);
int sp_buthp_destroy(sp_buthp **p);
int sp_buthp_init(sp_data *sp, sp_buthp *p);
int sp_buthp_compute(sp_data *sp, sp_buthp *p, SPFLOAT *in, SPFLOAT *out);
int sp_butter_filter(SPFLOAT *in, SPFLOAT *out, SPFLOAT *a);
typedef struct{
size_t size;
void *auxp;
}auxData;
typedef struct {
    int         writePos;
    int         bufferSize;
    int         readPos;
    int         readPosFrac;
    int         readPosFrac_inc;
    int         dummy;
    int         seedVal;
    int         randLine_cnt;
    SPFLOAT      filterState;
    SPFLOAT       *buf;
} sp_revsc_dl;

typedef struct  {
    SPFLOAT       aoutL, aoutR, ainL, ainR, kFeedBack, kLPFreq;
    SPFLOAT       iSampleRate, iPitchMod, iSkipInit;
    SPFLOAT      sampleRate;
    SPFLOAT      dampFact;
    SPFLOAT       prv_LPFreq;
    int         initDone;
    sp_revsc_dl delayLines[8];
    sp_auxdata *aux;
} sp_revsc;

/* TODO: merge alloc and create (assuming this method works... */
int sp_revsc_alloc(sp_data *sp, sp_auxdata *aux);
int sp_revsc_create(sp_data *sp, sp_revsc **p);
/* destroys user allocated data as well */
int sp_revsc_destroy(sp_revsc **p, sp_auxdata *aux); 
int sp_revsc_init(sp_data *sp, sp_revsc *p, sp_auxdata *aux);
int sp_revsc_compute(sp_data *sp, sp_revsc *p, SPFLOAT *in, SPFLOAT *out);
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
typedef struct {
    SPFLOAT freq, amp, iphs;
    int32_t   lphs;
    sp_ftbl *tbl;
} sp_osc;

int sp_osc_create(sp_osc **osc);
int sp_osc_destroy(sp_osc **osc);
int sp_osc_init(sp_data *sp, sp_osc *osc, sp_ftbl *ft);
int sp_osc_compute(sp_data *sp, sp_osc *osc, SPFLOAT *in, SPFLOAT *out);
typedef struct {
    SPFLOAT freq, amp, iphs;
    sp_ftbl *tbl;
    int32_t tablen;
    SPFLOAT tablenUPsr;
    SPFLOAT phs;
    SPFLOAT onedsr;
} sp_posc3;

int sp_posc3_create(sp_posc3 **posc3);
int sp_posc3_destroy(sp_posc3 **posc3);
int sp_posc3_init(sp_data *sp, sp_posc3 *posc3, sp_ftbl *ft);
int sp_posc3_compute(sp_data *sp, sp_posc3 *posc3, SPFLOAT *in, SPFLOAT *out);
#define sp_oneUp31Bit      (4.656612875245796924105750827168e-10)

#define sp_randGab   ((SPFLOAT)     \
        (((p->holdrand = p->holdrand * 214013 + 2531011) >> 1)  \
         & 0x7fffffff) * sp_oneUp31Bit)

typedef struct {
    SPFLOAT min, max, cps, mode, fstval;
    int16_t cpscod;
    int32_t phs;
    SPFLOAT num1, num2, dfdmax;
    int holdrand;
    SPFLOAT sicvt;
} sp_randi;

int sp_randi_create(sp_randi **p);
int sp_randi_destroy(sp_randi **p);
int sp_randi_init(sp_data *sp, sp_randi *p, int seed);
int sp_randi_compute(sp_data *sp, sp_randi *p, SPFLOAT *in, SPFLOAT *out);
typedef struct {
    SPFLOAT gg;
    SPFLOAT outputs;
    SPFLOAT inputs;
    SPFLOAT gain;
} sp_dcblock;

int sp_dcblock_create(sp_dcblock **p);
int sp_dcblock_destroy(sp_dcblock **p);
int sp_dcblock_init(sp_data *sp, sp_dcblock *p);
int sp_dcblock_compute(sp_data *sp, sp_dcblock *p, SPFLOAT *in, SPFLOAT *out);
typedef struct{
    void (*reinit)(void *);
    void (*compute)(void *, SPFLOAT *out);
    void *ud;
}sp_tevent;

int sp_tevent_create(sp_tevent **te);
int sp_tevent_destroy(sp_tevent **te);
int sp_tevent_init(sp_data *sp, sp_tevent *te, 
        void (*reinit)(void*), void (*compute)(void *, SPFLOAT *out), void *ud);
int sp_tevent_compute(sp_data *sp, sp_tevent *te, SPFLOAT *in, SPFLOAT *out);
typedef struct sp_metro{
    SPFLOAT sr, cps, iphs;
    SPFLOAT curphs;
    int flag;
    SPFLOAT onedsr;
} sp_metro;

int sp_metro_create(sp_metro **p);
int sp_metro_destroy(sp_metro **p);
int sp_metro_init(sp_data *sp, sp_metro *p);
int sp_metro_compute(sp_data *sp, sp_metro *p, SPFLOAT *in, SPFLOAT *out);
typedef struct sp_tenv{
    sp_tevent *te;
    uint32_t pos, atk_end, rel_start, sr, totaldur;
    SPFLOAT atk, rel, hold;
    SPFLOAT atk_slp, rel_slp;
    SPFLOAT last;
} sp_tenv;

int sp_tenv_create(sp_tenv **p);
int sp_tenv_destroy(sp_tenv **p);
int sp_tenv_init(sp_data *sp, sp_tenv *p, SPFLOAT atk, SPFLOAT hold, SPFLOAT rel);
void sp_tenv_reinit(void *ud);
void sp_tenv_comp(void *ud, SPFLOAT *out);
int sp_tenv_compute(sp_data *sp, sp_tenv *p, SPFLOAT *in, SPFLOAT *out);
typedef struct sp_maygate{
    SPFLOAT prob;
    SPFLOAT gate;
} sp_maygate;

int sp_maygate_create(sp_maygate **p);
int sp_maygate_destroy(sp_maygate **p);
int sp_maygate_init(sp_data *sp, sp_maygate *p, SPFLOAT prob);
int sp_maygate_compute(sp_data *sp, sp_maygate *p, SPFLOAT *in, SPFLOAT *out);
typedef struct{
    SPFLOAT freq, ris, dec, istor;
    SPFLOAT tpidsr;
    SPFLOAT sr;
    SPFLOAT delay[4];
}sp_fofilt;

int sp_fofilt_create(sp_fofilt **t);
int sp_fofilt_destroy(sp_fofilt **t);
int sp_fofilt_init(sp_data *sp, sp_fofilt *p);
int sp_fofilt_compute(sp_data *sp, sp_fofilt *p, SPFLOAT *in, SPFLOAT *out);

typedef struct{
    SPFLOAT b0, b1, b2, a0, a1, a2, reinit, xnm1, xnm2, ynm1, ynm2, cutoff, res;
    SPFLOAT sr;
    SPFLOAT tpidsr;
}sp_biquad;

int sp_biquad_create(sp_biquad **p);
int sp_biquad_destroy(sp_biquad **p);
int sp_biquad_init(sp_data *sp, sp_biquad *p);
int sp_biquad_compute(sp_data *sp, sp_biquad *p, SPFLOAT *in, SPFLOAT *out);
