#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sndfile.h>
#include "soundpipe.h"


sp_data *sp;
sp_ftbl *ft;
sp_paulstretch *ps;

static void process(sp_data *sp, void *ud)
{
    SPFLOAT out;
    sp_paulstretch_compute(sp, ps, NULL, &out);
    sp_out(sp, 0, out);
}


/* a little kluge to get file info */
static int get_info(const char *fname,
                    int *sr,
                    unsigned long *len)
{
    SF_INFO info;
    SNDFILE *snd;

    snd = sf_open(fname, SFM_READ, &info);
    if (snd == NULL) return 0;

    *sr = info.samplerate;
    *len = info.frames;
    sf_close(snd);
    return 1;
}

int main(int argc, char *argv[])
{
    SPFLOAT stretch;
    SPFLOAT window;
    uint32_t out_dur;
    const char *fin;
    const char *fout;
    unsigned long len;
    int rc;

    if(argc < 5) {
        fprintf(stderr,
            "Usage: %s window_size stretch in.wav out.wav\n",
            argv[0]
        );
        return 1;
    }

    sp_create(&sp);

    printf("samplerate = %d\n", atoi(argv[1]));

    sp_paulstretch_create(&ps);

    fin = argv[3];
    fout = argv[4];
    rc = get_info(fin, &sp->sr, &sp->len);

    if (!rc) {
        printf("There was a problem with the file '%s'\n",
               fin);
        goto cleanup;
    }

    printf("window = %g\n", atof(argv[1]));
    window = atof(argv[1]);
    printf("stretch = %g\n", atof(argv[2]));
    stretch = atof(argv[2]);
    sp->len *= stretch;
    printf("total dur = %gs\n", (SPFLOAT)sp->len / sp->sr);
    printf("input = %s\n", fin);
    sp_ftbl_loadfile(sp, &ft, fin);
    printf("output = %s\n", fout);

    strncpy(sp->filename, fout, 60);

    sp_paulstretch_init(sp, ps, ft, window, stretch);

    ps->wrap = 0;

    sp_process(sp, NULL, process);

    cleanup:

    sp_ftbl_destroy(&ft);
    sp_paulstretch_destroy(&ps);
    sp_destroy(&sp);
    return 0;
}
