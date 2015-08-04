#include <stdlib.h>
#include <string.h>
#include "soundpipe.h"
#include "ini.h"

int nano_create(nanosamp **smp, const char *wav, const char *ini)
{
    *smp = malloc(sizeof(nanosamp));
    nanosamp *psmp = *smp;
    strcpy(psmp->ini, ini);
    strcpy(psmp->wav, wav);
    psmp->info.format = 0;
    psmp->sndfile = sf_open(wav, SFM_READ, &psmp->info); 
    psmp->dict.last = &psmp->dict.root;
    psmp->dict.nval = 0;
    psmp->dict.init = 1;
    psmp->selected = 0;
    psmp->curpos = 0;
    if(psmp->info.frames < 1024) {
        psmp->bufsize = psmp->info.frames;
    } else {
        psmp->bufsize = 1024;
    }
    if(ini_parse(psmp->ini, nano_ini_handler, psmp) < 0) {
        printf("Can't load file %s\n", psmp->ini);
        return SP_NOT_OK;
    }

    return SP_OK;
}

int nano_select_from_index(nanosamp *smp, uint32_t pos)
{
    pos %= smp->dict.nval;
    smp->selected = 1;
    smp->sample = smp->index[pos];
    smp->counter = 0;
    smp->curpos = 0;
    sf_seek(smp->sndfile, smp->sample->pos, SEEK_SET);
    return SP_OK;
}

uint32_t nano_keyword_to_index(nanosamp *smp, const char *keyword)
{
    uint32_t i;
    for (i = 0; i < smp->dict.nval; i++) {
        if(strcmp(keyword, smp->index[i]->name)) {
            return i;
        }
    }
    return 0;
}

int nano_select(nanosamp *smp, const char *keyword)
{
    uint32_t i;
    nano_dict *dict = &smp->dict;
    nano_entry *entry = dict->root.next;
    smp->curpos = 0;
    smp->selected = 0;
    for(i = 0; i < dict->nval; i++) {
        if(strncmp(keyword, entry->name, 50) == 0) {
            smp->selected = 1;
            smp->sample = entry;
            smp->counter = 0;
            smp->curpos = 0;
            sf_seek(smp->sndfile, entry->pos, SEEK_SET);
            break;
        } else {
            entry = entry->next;
        } 
    }

    if(smp->selected == 1) return SP_OK;
    else return SP_NOT_OK;
}

int nano_ini_handler(void *user, const char *section, const char *name,
        const char *value)
{
    nanosamp *ss = user;
    nano_dict *dict = &ss->dict;
    const char *entry_name = dict->last->name; 

    if(dict->init) {
        nano_dict_add(dict, section);
        dict->init = 0;
    } else if(strncmp(entry_name, section, 50) != 0) {
        nano_dict_add(dict, section);
    }

    if(strcmp(name, "pos") == 0) {
        dict->last->pos = (uint32_t)(atof(value) * ss->info.samplerate);
    } else if(strcmp(name, "size") == 0) {
        dict->last->size= (uint32_t)(atof(value) * ss->info.samplerate);
    }

    return SP_OK;
}

int nano_compute(nanosamp *smp, float *out)
{
    if(!smp->selected) {
        *out = 0;
        return SP_NOT_OK; 
    }

    if(smp->counter == 0 && smp->selected) {
        memset(smp->buf, 0, sizeof(float) * 1024);
        smp->bufsize = sf_read_float(smp->sndfile, smp->buf, smp->bufsize);
    }

    if(smp->curpos < smp->sample->size) {
        *out = smp->buf[smp->counter]; 

        if(smp->bufsize) {
            smp->counter++;
            smp->counter %= smp->bufsize;
        }
        smp->curpos++;
    } else {
        smp->selected = 0;
        *out = 0;
    }
    return SP_OK;
}

int nano_destroy(nanosamp **smp)
{
    nanosamp *psmp = *smp;
    sf_close(psmp->sndfile);
    nano_dict_destroy(&psmp->dict);
    free(*smp);
    return SP_OK;
}

int nano_dict_add(nano_dict *dict, const char *name)
{
    nano_entry *entry = malloc(sizeof(nano_entry));
    strcpy(entry->name, name);
    dict->last->next = entry;
    dict->last = entry;
    dict->nval++;
    return SP_OK;
}

int nano_dict_destroy(nano_dict *dict)
{
    int i;
    nano_entry *entry, *next;
    entry = dict->root.next;

    for(i = 0; i < dict->nval; i++) {
        next = entry->next;
        free(entry);
        entry = next;
    }

    return SP_OK;
}

int nano_create_index(nanosamp *smp)
{
    nano_dict *dict = &smp->dict;
    //nano_entry *ip = malloc(dict->nval * sizeof(nano_entry *));
    smp->index = malloc(dict->nval * sizeof(nano_entry *));
    int i;
    nano_entry *entry, *next;
    entry = dict->root.next;
    
    for(i = 0; i < dict->nval; i++) {
        next = entry->next;
        smp->index[i] = entry;
        entry = next;
    }
    //smp->index = ip;
    return SP_OK;
}

int nano_destroy_index(nanosamp *smp)
{
    free(smp->index);
    return SP_OK;
}

int sp_nsmp_create(sp_nsmp **p)
{
    *p = malloc(sizeof(sp_nsmp));
    return SP_OK;
}

int sp_nsmp_destroy(sp_nsmp **p)
{
    sp_nsmp *pp = *p;
    nano_destroy_index(pp->smp);
    nano_destroy(&pp->smp);
    free(*p);
    return SP_OK;
}

int sp_nsmp_init(sp_data *sp, sp_nsmp *p, const char *wav, const char *ini)
{
    if (nano_create(&p->smp, wav, ini) == SP_NOT_OK) {
        nano_destroy(&p->smp);
        return SP_NOT_OK;
    }
    nano_create_index(p->smp);
    p->index= 0;
    p->triggered = 0;
    return SP_OK;
}

int sp_nsmp_compute(sp_data *sp, sp_nsmp *p, SPFLOAT *trig, SPFLOAT *out)
{
    if (*trig != 0) {
       p->triggered = 1; 
       nano_select_from_index(p->smp, p->index);
    }

    if(p->triggered == 1) {
        nano_compute(p->smp, out);
    } else {
        *out = 0;
    }

    return SP_OK;
}

int sp_nsmp_print_index(sp_data *sp, sp_nsmp *p)
{
    uint32_t i;
    for(i = 0; i < p->smp->dict.nval; i++) {
        printf("%d: key = %s\n", i, p->smp->index[i]->name);
    }
    return SP_OK;
}

