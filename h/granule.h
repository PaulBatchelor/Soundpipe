#ifndef SP_GRANDULE_MAXVOICE
#define SP_GRANULE_MAXVOICE 128
#endif

typedef struct {
    SPFLOAT ar, xamp, ivoice, iratio;
    SPFLOAT imode, ithd, ifn, ipshift;
    SPFLOAT igskip;
    SPFLOAT igskip_os;
    SPFLOAT ilength, kgap, igap_os, kgsize, igsize_os, iatt, idec;
    SPFLOAT iseed, ipitch1, ipitch2, ipitch3, ipitch4, ifnenv;
    int32_t fpnt[SP_GRANULE_MAXVOICE];
    int32_t cnt[SP_GRANULE_MAXVOICE];
    int32_t gskip[SP_GRANULE_MAXVOICE];
    int32_t gap[SP_GRANULE_MAXVOICE];
    int32_t gsize[SP_GRANULE_MAXVOICE];
    int32_t stretch[SP_GRANULE_MAXVOICE];
    int32_t mode[SP_GRANULE_MAXVOICE];
    SPFLOAT pshift[SP_GRANULE_MAXVOICE];
    SPFLOAT phs[SP_GRANULE_MAXVOICE];
    int16_t grnd;
    int32_t gskip_os;
    int32_t gstart, gend, glength;
    SPFLOAT gap_os, gsize_os;
    sp_ftbl *ftp, *ftp_env;
} sp_granule;

int sp_granule_create(sp_granule **p);
int sp_granule_destroy(sp_granule **p);
int sp_granule_init(sp_data *sp, sp_granule *p,
                    SPFLOAT ivoice,
                    SPFLOAT iratio,
                    SPFLOAT imode,
                    SPFLOAT ithd,
                    sp_ftbl *ft,
                    SPFLOAT ipshift,
                    SPFLOAT igskip,
                    SPFLOAT igskip_os,
                    SPFLOAT igsize_os,
                    SPFLOAT ilength,
                    SPFLOAT igap_os,
                    SPFLOAT iatt,
                    SPFLOAT idec,
                    SPFLOAT iseed,
                    SPFLOAT ipitch1,
                    SPFLOAT ipitch2,
                    SPFLOAT ipitch3,
                    SPFLOAT ipitch4,
                    sp_ftbl *ft_env);
int sp_granule_compute(sp_data *sp, sp_granule *p, SPFLOAT *in, SPFLOAT *out);
