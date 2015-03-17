#include <sndfile.h>
#define SP_BUFSIZE 4096
#define SPFLOAT float

typedef struct sp_data{ 
    SPFLOAT buf[SP_BUFSIZE];
    SPFLOAT out;
    SNDFILE *sf;
    int sr;
    long len;
    char filename[200];
}sp_data; 

int sp_create(sp_data **spp);
int sp_destroy(sp_data **spp);
int sp_process(sp_data *sp, void *ud, void (*callback)(sp_data *, void *));
