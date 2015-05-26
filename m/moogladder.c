typedef struct _moogladder {
  OPDS    h;
  MYFLT   *out;
  MYFLT   *in;
  MYFLT   *freq;
  MYFLT   *res;
  MYFLT   *istor;

  double  delay[6];
  double  tanhstg[3];
  MYFLT   oldfreq;
  MYFLT   oldres;
  double  oldacr;
  double  oldtune;
} moogladder;
static int moogladder_init(CSOUND *csound,moogladder *p)
{
    int i;
    if (*p->istor == FL(0.0)) {
      for (i = 0; i < 6; i++)
        p->delay[i] = 0.0;
      for (i = 0; i < 3; i++)
        p->tanhstg[i] = 0.0;
      p->oldfreq = FL(0.0);
      p->oldres = -FL(1.0);     /* ensure calculation on first cycle */
    }
    return OK;
}

static int moogladder_process(CSOUND *csound,moogladder *p)
{
    MYFLT   *out = p->out;
    MYFLT   *in = p->in;
    MYFLT   freq = *p->freq;
    MYFLT   res = *p->res;
    double  res4;
    double  *delay = p->delay;
    double  *tanhstg = p->tanhstg;
    double  stg[4], input;
    double  acr, tune;
#define THERMAL (0.000025) /* (1.0 / 40000.0) transistor thermal voltage  */
    int     j, k;
    uint32_t offset = p->h.insdshead->ksmps_offset;
    uint32_t early  = p->h.insdshead->ksmps_no_end;
    uint32_t i, nsmps = CS_KSMPS;

    if (res < 0) res = 0;

    if (p->oldfreq != freq || p->oldres != res) {
      double  f, fc, fc2, fc3, fcr;
      p->oldfreq = freq;
      /* sr is half the actual filter sampling rate  */
      fc =  (double)(freq/CS_ESR);
      f  =  0.5*fc;
      fc2 = fc*fc;
      fc3 = fc2*fc;
      /* frequency & amplitude correction  */
      fcr = 1.8730*fc3 + 0.4955*fc2 - 0.6490*fc + 0.9988;
      acr = -3.9364*fc2 + 1.8409*fc + 0.9968;
      tune = (1.0 - exp(-(TWOPI*f*fcr))) / THERMAL;   /* filter tuning  */
      p->oldres = res;
      p->oldacr = acr;
      p->oldtune = tune;
    }
    else {
      res = p->oldres;
      acr = p->oldacr;
      tune = p->oldtune;
    }
    res4 = 4.0*(double)res*acr;

    if (UNLIKELY(offset)) memset(out, '\0', offset*sizeof(MYFLT));
    if (UNLIKELY(early)) {
      nsmps -= early;
      memset(&out[nsmps], '\0', early*sizeof(MYFLT));
    }
    for (i = offset; i < nsmps; i++) {
      /* oversampling  */
      for (j = 0; j < 2; j++) {
        /* filter stages  */
        input = in[i] - res4 /*4.0*res*acr*/ *delay[5];
        delay[0] = stg[0] = delay[0] + tune*(tanh(input*THERMAL) - tanhstg[0]);
#if 0
        input = stg[0];
        stg[1] = delay[1] + tune*((tanhstg[0] = tanh(input*THERMAL)) - tanhstg[1]);
        input = delay[1] = stg[1];
        stg[2] = delay[2] + tune*((tanhstg[1] = tanh(input*THERMAL)) - tanhstg[2]);
        input = delay[2] = stg[2];
        stg[3] = delay[3] + tune*((tanhstg[2] =
                                   tanh(input*THERMAL)) - tanh(delay[3]*THERMAL));
        delay[3] = stg[3];
#else
        for (k = 1; k < 4; k++) {
          input = stg[k-1];
          stg[k] = delay[k]
            + tune*((tanhstg[k-1] = tanh(input*THERMAL))
                    - (k != 3 ? tanhstg[k] : tanh(delay[k]*THERMAL)));
          delay[k] = stg[k];
        }
#endif
        /* 1/2-sample delay for phase compensation  */
        delay[5] = (stg[3] + delay[4])*0.5;
        delay[4] = stg[3];
      }
      out[i] = (MYFLT) delay[5];
    }
    return OK;
}
