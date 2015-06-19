/*
 * Planet
 * 
 * This code has been extracted from the Csound opcode "Planet".
 * It has been modified to work as a Soundpipe module.
 * 
 * Original Author(s): Hans Mikelson 
 * Year: 1998
 * Location: Opcodes/biquad.c
 *
 */


#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#define ROOT2 (1.4142135623730950488)

#ifndef M_PI
#define M_PI		3.14159265358979323846	/* pi */
#endif 

#include "soundpipe.h"

int sp_planet_create(sp_planet **p)
{
    *p = malloc(sizeof(sp_planet));
    return SP_OK;
}

int sp_planet_destroy(sp_planet **p)
{
    free(*p);
    return SP_OK;
}

int sp_planet_init(sp_data *sp, sp_planet *p)
{
    p->iskip = 0.0;

    if(p->iskip == 0.0){
        p->x  = p->xval;  p->y  = p->yval;  p->z  = p->zval;
        p->vx = p->vxval; p->vy = p->vyval; p->vz = p->vzval;
        p->ax = 0.0; p->ay = 0.0; p->az = 0.0;
        p->hstep = p->delta;
        p->friction = 1.0 - p->fric/10000.0;
    }
    return SP_OK;
}

int sp_planet_compute(sp_data *sp, sp_planet *p, SPFLOAT *in, SPFLOAT *out)
{

    SPFLOAT outx, outy, outz;
    SPFLOAT   sqradius1, sqradius2, radius1, radius2, fric;
    SPFLOAT xxpyy, dz1, dz2, mass1, mass2, msqror1, msqror2;

    fric = p->friction;

    outx = p->outx;
    outy = p->outy;
    outz = p->outz;

    p->s1z = p->sep*0.5;
    p->s2z = -p->s1z;

    mass1 = p->mass1;
    mass2 = p->mass2;

      xxpyy = p->x * p->x + p->y * p->y;
      dz1 = p->s1z - p->z;

      /* Calculate Acceleration */
      sqradius1 = xxpyy + dz1 * dz1 + 1.0;
      radius1 = sqrt(sqradius1);
      msqror1 = mass1/sqradius1/radius1;

      p->ax = msqror1 * -p->x;
      p->ay = msqror1 * -p->y;
      p->az = msqror1 * dz1;

      dz2 = p->s2z - p->z;

      /* Calculate Acceleration */
      sqradius2 = xxpyy + dz2 * dz2 + 1.0;
      radius2 = sqrt(sqradius2);
      msqror2 = mass2/sqradius2/radius2;

      p->ax += msqror2 * -p->x;
      p->ay += msqror2 * -p->y;
      p->az += msqror2 * dz2;

      /* Update Velocity */
      p->vx = fric * p->vx + p->hstep * p->ax;
      p->vy = fric * p->vy + p->hstep * p->ay;
      p->vz = fric * p->vz + p->hstep * p->az;

      /* Update Position */
      p->x += p->hstep * p->vx;
      p->y += p->hstep * p->vy;
      p->z += p->hstep * p->vz;

      /* Output the results */
      outx = p->x;
      outy = p->y;
      outz = p->z;
    
    return OK;
}
