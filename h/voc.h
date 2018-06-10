
#ifndef SP_VOC
#define SP_VOC
typedef struct sp_voc sp_voc;

int sp_voc_create(sp_voc **voc);
int sp_voc_destroy(sp_voc **voc);
int sp_voc_init(sp_data *sp, sp_voc *voc);
int sp_voc_compute(sp_data *sp, sp_voc *voc, SPFLOAT *out);
int sp_voc_tract_compute(sp_data *sp, sp_voc *voc, SPFLOAT *in, SPFLOAT *out);

void sp_voc_set_frequency(sp_voc *voc, SPFLOAT freq);
SPFLOAT * sp_voc_get_frequency_ptr(sp_voc *voc);

SPFLOAT* sp_voc_get_tract_diameters(sp_voc *voc);
SPFLOAT* sp_voc_get_current_tract_diameters(sp_voc *voc);
int sp_voc_get_tract_size(sp_voc *voc);
SPFLOAT* sp_voc_get_nose_diameters(sp_voc *voc);
int sp_voc_get_nose_size(sp_voc *voc);
void sp_voc_set_tongue_shape(sp_voc *voc,
    SPFLOAT tongue_index,
    SPFLOAT tongue_diameter);
void sp_voc_set_tenseness(sp_voc *voc, SPFLOAT breathiness);
SPFLOAT * sp_voc_get_tenseness_ptr(sp_voc *voc);
void sp_voc_set_velum(sp_voc *voc, SPFLOAT velum);
SPFLOAT * sp_voc_get_velum_ptr(sp_voc *voc);

void sp_voc_set_diameters(sp_voc *voc,
    int blade_start,
    int lip_start,
    int tip_start,
    SPFLOAT tongue_index,
    SPFLOAT tongue_diameter,
    SPFLOAT *diameters);

int sp_voc_get_counter(sp_voc *voc);


#endif

