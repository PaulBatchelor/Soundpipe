typedef struct{
    SPFLOAT   outx, outy, outz, mass1, mass2, sep, xval, yval, zval;
    SPFLOAT   vxval, vyval, vzval, delta, fric, iskip;
    SPFLOAT   s1z, s2z, friction;
    SPFLOAT   x, y, z, vx, vy, vz, ax, ay, az, hstep;
}sp_planet;

int sp_planet_create(sp_planet **p);
int sp_planet_destroy(sp_planet **p);
int sp_planet_init(sp_data *sp, sp_planet *p);
int sp_planet_compute(sp_data *sp, sp_planet *p, SPFLOAT *in, SPFLOAT *out);
