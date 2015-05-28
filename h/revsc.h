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

