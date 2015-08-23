/*
 * pluck
 * 
 * This code has been extracted from the Csound opcode "repluck"
 * It has been modified to work as a Soundpipe module.
 * 
 * Original Author(s): John ffitch
 * Year: 1996
 * Location: Opcodes/repluck.c
 *
 */

#include <stdlib.h>
#include <string.h>
#include "soundpipe.h"
#define OVERCNT (256)
#define OVERSHT (8)
#define OVERMSK (0xFF)

typedef struct {
    SPFLOAT *data;
    int length;
    SPFLOAT *pointer;
    SPFLOAT *end;
} DelayLine;

static SPFLOAT * locate(DelayLine *dl, int position)
{
    SPFLOAT *outloc = dl->pointer + position;
    while (outloc < dl->data)
      outloc += dl->length;
    while (outloc > dl->end)
      outloc -= dl->length;
    return outloc;
}

static SPFLOAT getvalue(DelayLine *dl, int position)
{
    SPFLOAT *outloc = dl->pointer + position;
    while (outloc < dl->data)
      outloc += dl->length;
    while (outloc > dl->end)
      outloc -= dl->length;
    return *outloc;
}

int sp_pluck_create(sp_pluck **p)
{
    *p = malloc(sizeof(sp_pluck));
    return SP_OK;
}

int sp_pluck_destroy(sp_pluck **p)
{
    sp_pluck *pp = *p;
    sp_auxdata_free(&pp->upper);
    sp_auxdata_free(&pp->lower);
    sp_auxdata_free(&pp->up_data);
    sp_auxdata_free(&pp->down_data);
    free(*p);
    return SP_OK;
}

static int pluck_setup(sp_data *sp, sp_pluck *p) 
{
    int npts;
    int pickpt;
    int rail_len;
    SPFLOAT upslope;
    SPFLOAT downslope;
    SPFLOAT *initial_shape;
    int i;
    int scale = 1;
    DelayLine *upper_rail;
    DelayLine *lower_rail;
    SPFLOAT plk = p->plk;
                                
    npts = (int)(sp->sr / p->freq); /* Length of full delay */

    /* Minimum rail length is 256 */
    while (npts < 512) {        
      npts += (int)(sp->sr / p->freq);
      scale++;
    }

    rail_len = npts / 2;

    if (plk >= 1.0 || plk <= 0.0) {
      plk = 0.5;
    }

    pickpt = (int)(rail_len * plk);

    upper_rail = (DelayLine*)p->upper.ptr;
    upper_rail->length = rail_len;
    upper_rail->data = (SPFLOAT *)p->up_data.ptr;
    upper_rail->pointer = upper_rail->data;
    upper_rail->end = upper_rail->data + rail_len - 1;
    lower_rail = (DelayLine*)p->lower.ptr;
    lower_rail->length = rail_len;
    lower_rail->data = (SPFLOAT *)p->down_data.ptr;
    lower_rail->pointer = lower_rail->data;
    lower_rail->end = lower_rail->data + rail_len - 1;

                                /* Set initial shape */
    if (plk != 0.0) {
      initial_shape = (SPFLOAT *) malloc(rail_len * sizeof(SPFLOAT));
      if (pickpt < 1) pickpt = 1;  /* Place for pluck, in range (0,1.0) */
      upslope = 1.0 / (SPFLOAT)pickpt;  /* Slightly faster to precalculate */
      downslope = 1.0 / (SPFLOAT)(rail_len - pickpt - 1);
      for (i = 0; i < pickpt; i++)
        initial_shape[i] = upslope * i;
      for (i = pickpt; i < rail_len; i++)
        initial_shape[i] = downslope * (rail_len - 1 - i);
      for (i=0; i< rail_len; i++)
        upper_rail->data[i] = 0.5 * initial_shape[i];
      for (i=0; i< rail_len; i++)
        lower_rail->data[i] = 0.5 * initial_shape[i];
      free(initial_shape);
    } else {
      memset(upper_rail->data, 0, rail_len * sizeof(SPFLOAT));
      memset(lower_rail->data, 0, rail_len * sizeof(SPFLOAT));
    }
    p->state = 0.0;         /* filter memory */
    p->rail_len = rail_len;
    p->scale = scale;
    return SP_OK;
}

int sp_pluck_init(sp_data *sp, sp_pluck *p, SPFLOAT ifreq)
{
    p->plk = 0.75;
    p->amp = 0.8;
    p->freq = ifreq;
    p->ifreq = ifreq;
    p->reflect = 0.95;
    p->pickup = 0.75;

    int npts;
    int rail_len;
    int scale = 1;
    SPFLOAT plk = p->plk;
                                
    npts = (int)(sp->sr / p->freq); /* Length of full delay */

    /* Minimum rail length is 256 */
    while (npts < 512) {        
      npts += (int)(sp->sr / p->freq);
      scale++;
    }

    rail_len = npts / 2;

    if (plk >= 1.0 || plk <= 0.0) {
      plk = 0.5;
    }


    sp_auxdata_alloc(&p->upper, sizeof(DelayLine));
    sp_auxdata_alloc(&p->up_data, rail_len * sizeof(SPFLOAT));
    sp_auxdata_alloc(&p->lower, sizeof(DelayLine));
    sp_auxdata_alloc(&p->down_data, rail_len*sizeof(SPFLOAT));
  
    pluck_setup(sp, p); 

    return SP_OK;
}

int sp_pluck_compute(sp_data *sp, sp_pluck *p, SPFLOAT *trig, SPFLOAT *in, SPFLOAT *out)
{
    SPFLOAT yp0,ym0,ypM,ymM;
    DelayLine   *upper_rail;
    DelayLine   *lower_rail;
    int pickup, pickfrac;
    int i;
    int scale;
    SPFLOAT state = p->state;
    SPFLOAT reflect = p->reflect;


    if (reflect <= 0.0 || reflect >= 1.0) {
      reflect = 0.5;
    }
    scale = p->scale;
    reflect = 1.0 - (1.0 - reflect)/scale; /* For over sapling */
    upper_rail = (DelayLine*)p->upper.ptr;
    lower_rail = (DelayLine*)p->lower.ptr;
    
    if(*trig) {
        pluck_setup(sp, p);
    }

    /* fractional delays */
    pickup = (int)((SPFLOAT)OVERCNT * p->pickup * p->rail_len);
    pickfrac = pickup & OVERMSK;
    pickup = pickup>>OVERSHT;
    if (pickup< 0 || pickup > p->rail_len) {
      pickup   = p->rail_len * (OVERCNT/2);
      pickfrac = pickup & OVERMSK;
      pickup   = pickup>>OVERSHT;
    }

    //for (n=offset;n<nsmps;n++) {
      SPFLOAT s, s1;
      s = getvalue(upper_rail, pickup) + getvalue(lower_rail, pickup);
      s1 = getvalue(upper_rail, pickup+1) + getvalue(lower_rail, pickup+1);
    /* Fractional delay */
      *out = s + (s1 - s)*(SPFLOAT)pickfrac/(SPFLOAT)OVERCNT; 
      if (in != NULL) {        
        /* Excite the string from input */
        SPFLOAT *loc = locate(lower_rail,1);
        *loc += (0.5 * *in)/(p->amp);
        loc = locate(upper_rail,1);
        *loc += (0.5 * *in) / (p->amp);
      }
      *out *= p->amp;        
      /* Loop for precision figure */
      for (i=0; i<scale; i++) { 
/* Sample traveling into "bridge" */
        ym0 = getvalue(lower_rail, 1); 
/* Sample to "nut" */
        ypM = getvalue(upper_rail, upper_rail->length - 2); 
        /* Inverting reflection at rigid nut */
        /* reflection at yielding bridge */
        /* Implement a one-pole lowpass with
           feedback coefficient from input */
        ymM = -ypM;             
        state = (state * reflect) + ym0 * (1.0 - reflect);
        /* String state update */
        /* Decrement pointer and then update */
        yp0 = - state;          
        {
          SPFLOAT *ptr = upper_rail->pointer;
          ptr--;
          if (ptr < upper_rail->data)
            ptr = upper_rail->end;
          *ptr = yp0;
          upper_rail->pointer = ptr;
        }
                                
        {
          SPFLOAT *ptr = lower_rail->pointer;
          *ptr = ymM;
          ptr++;
          if (ptr > lower_rail->end)
            ptr = lower_rail->data;
          lower_rail->pointer = ptr;
        }
      }
    //};
    p->state = state;           

    return SP_OK;
}
