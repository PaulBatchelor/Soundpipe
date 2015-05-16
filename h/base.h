#include <sndfile.h>
#define SP_BUFSIZE 4096
#define SPFLOAT float
#define SP_OK 1
#define SP_NOT_OK 0

#ifndef __SOUNDPIPE_H__
#define __SOUNDPIPE_H__
#endif

typedef unsigned long sp_frame;

typedef struct sp_data{ 
    SPFLOAT buf[SP_BUFSIZE];
    SPFLOAT out;
    SNDFILE *sf;
    int sr;
    unsigned long len;
    unsigned long pos;
    char filename[200];
}sp_data; 

int sp_create(sp_data **spp);
int sp_destroy(sp_data **spp);
int sp_process(sp_data *sp, void *ud, void (*callback)(sp_data *, void *));
