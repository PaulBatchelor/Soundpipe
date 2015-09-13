#include <stdlib.h>
#include <stdio.h>
#include "soundpipe.h"
#include "md5.h"
#include "test.h"

int sp_test_create(sp_test **t, uint32_t bufsize)
{
    uint32_t i;
    *t = malloc(sizeof(sp_test));
    sp_test *tp = *t;

    SPFLOAT *buf = malloc(sizeof(SPFLOAT) * bufsize);
    for(i = 0; i < bufsize; i++) tp->buf = 0; 

    tp->buf = buf;
    tp->size = bufsize;
    tp->pos = 0;
    md5_init(&tp->state);
    tp->md5string[32] = '\0';
    return SP_OK;
}

int sp_test_destroy(sp_test **t)
{
    sp_test *tp = *t;
    free(tp->buf);
    free(*t);
    return SP_OK;
}

int sp_test_add_sample(sp_test *t, SPFLOAT sample)
{
    if(t->pos < t->size) {
        t->buf[t->pos] = sample;
        t->pos++;
    }
    return SP_OK;
}

int sp_test_compare(sp_test *t, const char *md5hash)
{
    md5_append(&t->state, (const md5_byte_t *)t->buf, sizeof(SPFLOAT) * t->size);
    md5_finish(&t->state, t->digest);
    int i;
    char in[3], out[3];
    unsigned char val;
    int fail = 0;
    for(i = 0; i < 16; i++) {
        in[0] = md5hash[2 * i];
        in[1] = md5hash[2 * i + 1];
        in[2] = '\0';
        sprintf(out, "%02x", t->digest[i]);
        t->md5string[2 * i] = out[0];
        t->md5string[2 * i + 1] = out[1];
        if(strcmp(in, out)) {
            fail = 1;
        }
    }

    if(fail) {
        return SP_NOT_OK;
    } else {
        return SP_OK;
    }
}

