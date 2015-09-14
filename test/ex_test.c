#include <stdlib.h>
#include <stdio.h>
#include "soundpipe.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    sp_osc *osc;
    sp_ftbl *ft;
} UserData;

void setup(sp_data *sp, void *udata) 
{
    UserData *ud = udata;

    sp_osc_create(&ud->osc);
    sp_ftbl_create(sp, &ud->ft, 4096);

    sp_gen_sine(sp, ud->ft);
    sp_osc_init(sp, ud->osc, ud->ft, 0);
}

void process(sp_data *sp, void *udata) 
{
    UserData *ud = udata;
    sp_osc_compute(sp, ud->osc, NULL, &sp->out[0]);
}

void destroy(sp_data *sp, void *udata)
{
    UserData *ud = udata;

    sp_osc_destroy(&ud->osc);
    sp_ftbl_destroy(&ud->ft);
}

int sp_test_process(sp_data *sp, 
        void (*process)(sp_data *, void *), 
        uint32_t bufsize,
        const char *hash,
        void *ud)
{
    sp_test *t;
    uint32_t n;
    int fail = 0;

    sp_test_create(&t, bufsize);
   
    for(n = 0; n < bufsize; n++) {
        process(sp, ud);
        sp_test_add_sample(t, sp->out[0]);
    }

    if(sp_test_compare(t, hash) == SP_NOT_OK) {
        printf("generated hash %s does not match reference hash %s\n", 
                t->md5string, hash);
        fail = 1;
    }

    sp_test_destroy(&t);
    if(fail) return SP_NOT_OK;
    else return SP_OK;
}

int main() 
{
    plan( 2 );
    sp_data *sp;
    uint32_t size = 44100 * 5;
    UserData ud;

    sp_create(&sp);

    setup(sp, &ud);

    const char *hash = "31628d6589000de3b2cda9997ca15581";
    const char *wronghash = "31628d6589000de3b2cda9997ca11234";

    ok(sp_test_process(sp, process, size, hash, &ud) == SP_OK, 
            "440Hz sine wave");
    ok(sp_test_process(sp, process, size, wronghash, &ud) == SP_OK, 
            "440Hz sine wave with wrong hash.");

    destroy(sp, &ud);
    sp_destroy(&sp);
    return 0;
}
