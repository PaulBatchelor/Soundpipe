#include <stdio.h>
#include "soundpipe.h"

typedef struct{
    sp_posc3 *posc[8];
    sp_revsc *rev;
    sp_ftbl *ft;
}udata;

void make_note(sp_data *sp, sp_posc3 *posc3, unsigned long counter, unsigned long clock, SPFLOAT *output)
{
   unsigned long count = counter % clock;
   if (count < 9600) {
       sp_posc3_compute(sp, posc3, NULL, output);
   } else {
       *output = 0;
   } 
}

void write_music(sp_data *sp, void *ud)
{
    udata *udp = ud;
    SPFLOAT out[8];
    SPFLOAT mix, verb, foo;
    for(int i = 0; i < 8; i++) {
        make_note(sp, udp->posc[i], sp->pos, ((i * 17600) + 17600), &out[i]);
    }
    mix = (out[0] * 0.2) + (out[1] * 0.2) + (out[2] * 0.2) + (out[3] * 0.2) + (out[4] * 0.2) + (out[5] * 0.2) 
       + (out[6] * 0.2) +  (out[7] * 0.2);
    sp_revsc_compute(sp, udp->rev, &mix, &mix, &verb, &foo);
    
    sp->out[0] = mix + (verb * 0.2);

}

int main()
{
    udata ud;
    sp_data *sp;
    sp_create(&sp);
    sp_ftbl_create(sp, &ud.ft, 4096);
    for(int i = 0; i < 8; i++) sp_posc3_create(&ud.posc[i]);
    sp_revsc_create(&ud.rev);
    sp_gen_sine(ud.ft);

    for(int i = 0; i < 8; i++) sp_posc3_init(sp, ud.posc[i], ud.ft);
    ud.posc[0]->freq = sp_midi2cps(48);
    ud.posc[1]->freq = sp_midi2cps(52);
    ud.posc[2]->freq = sp_midi2cps(59);
    ud.posc[3]->freq = sp_midi2cps(62);
    ud.posc[4]->freq = sp_midi2cps(72);
    ud.posc[5]->freq = sp_midi2cps(71);
    ud.posc[6]->freq = sp_midi2cps(69);
    ud.posc[7]->freq = sp_midi2cps(66);

    sp_revsc_init(sp, ud.rev);
    
    sp->len = 44100 * 20;
    sp_process(sp, &ud, write_music);

    for(int i = 0; i < 8; i++) sp_posc3_destroy(&ud.posc[i]);
    sp_revsc_destroy(&ud.rev);
    sp_ftbl_destroy(&ud.ft);
    sp_destroy(&sp);
    return 0;
}
