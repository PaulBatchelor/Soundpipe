//static void fftInit(sp_fft *fft, int M)
void sp_fft_init(sp_fft *fft, int M)
{
    /* malloc and init cosine and bit reversed tables for a given size  */
    /* fft, ifft, rfft, rifft                                           */
    /* INPUTS                                                           */
    /*   M = log2 of fft size (ex M=10 for 1024 point fft)              */
    /* OUTPUTS                                                          */
    /*   private cosine and bit reversed tables                         */

    //SPFLOAT **UtblArray;
    //int16_t **BRLowArray;
    SPFLOAT *utbl;
    int16_t *BRLow;
    int16_t *BRLowCpx;
    int i;

    //fft->FFT_table_1 = malloc(sizeof(SPFLOAT*) * 32);
    //fft->FFT_table_2 = malloc(sizeof(int16_t*) * 32);

    //for (i = 0; i < 32; i++) {
    //    ((SPFLOAT**) fft->FFT_table_1)[i] = (SPFLOAT*) NULL;
    //    ((int16_t**) fft->FFT_table_2)[i] = (int16_t*) NULL;
    //}

    //UtblArray = (SPFLOAT**) fft->FFT_table_1;
    //BRLowArray = (int16_t**) fft->FFT_table_2;

    /*** I did NOT test cases with M>27 ***/
    /* init cos table */
    utbl = (SPFLOAT*) malloc((POW2(M) / 4 + 1) * sizeof(SPFLOAT));
    fftCosInit(M, utbl);

    BRLowCpx =
      (int16_t*) malloc(POW2(M / 2 - 1) * sizeof(int16_t));
    fftBRInit(M, BRLowCpx);

  /* init bit reversed table for real FFT */
     BRLow =
      (int16_t*) malloc(POW2((M - 1) / 2 - 1) * sizeof(int16_t));
    fftBRInit(M - 1, BRLow);

    fft->BRLow = BRLow;
    fft->BRLowCpx = BRLowCpx;
    fft->utbl = utbl;

    //fft->FFT_max_size |= (1 << M);
}

//static inline int ConvertFFTSize(sp_fft *fft, int N)
//{
//    if (N <= 0)
//      return (-N);
//    switch (N) {
//      case 0x00000001:  return 0;
//      case 0x00000002:  return 1;
//      case 0x00000004:  return 2;
//      case 0x00000008:  return 3;
//      case 0x00000010:  return 4;
//      case 0x00000020:  return 5;
//      case 0x00000040:  return 6;
//      case 0x00000080:  return 7;
//      case 0x00000100:  return 8;
//      case 0x00000200:  return 9;
//      case 0x00000400:  return 10;
//      case 0x00000800:  return 11;
//      case 0x00001000:  return 12;
//      case 0x00002000:  return 13;
//      case 0x00004000:  return 14;
//      case 0x00008000:  return 15;
//      case 0x00010000:  return 16;
//      case 0x00020000:  return 17;
//      case 0x00040000:  return 18;
//      case 0x00080000:  return 19;
//      case 0x00100000:  return 20;
//      case 0x00200000:  return 21;
//      case 0x00400000:  return 22;
//      case 0x00800000:  return 23;
//      case 0x01000000:  return 24;
//      case 0x02000000:  return 25;
//      case 0x04000000:  return 26;
//      case 0x08000000:  return 27;
//      case 0x10000000:  return 28;
//    }
//    return 0;
//}

static inline void getTablePointers(sp_fft *p, SPFLOAT **ct, int16_t **bt,
                                                int cn, int bn)
{
    /*if (!(p->FFT_max_size & (1 << cn)))
      fftInit(p, cn);
      */
    //*ct = ((SPFLOAT**) p->FFT_table_1)[cn];
    //*bt = ((int16_t**) p->FFT_table_2)[bn];
}

void sp_fftr(sp_fft *fft, SPFLOAT *buf, int FFTsize)
{
    SPFLOAT *Utbl;
    int16_t *BRLow;
    int   M = log2(FFTsize);
    rffts1(buf, M, fft->utbl, fft->BRLow);
}

void sp_fft_cpx(sp_fft *fft, SPFLOAT *buf, int FFTsize)
{
    SPFLOAT *Utbl;
    int16_t *BRLow;
    int   M = log2(FFTsize);
    ffts1(buf, M, fft->utbl, fft->BRLowCpx);
}



void sp_ifftr(sp_fft *fft, SPFLOAT *buf, int FFTsize)
{
    SPFLOAT *Utbl;
    int16_t *BRLow;
    int   M = log2(FFTsize);
    riffts1(buf, M, fft->utbl, fft->BRLow);
}

void sp_fft_destroy(sp_fft *fft) 
{
    free(fft->utbl);
    free(fft->BRLow);
    free(fft->BRLowCpx);
}
