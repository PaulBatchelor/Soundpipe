#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "soundpipe.h"
#ifndef M_PI
#define M_PI		3.14159265358979323846	
#endif 
#define WUTR_SOUND_DECAY 0.95
#define WUTR_SYSTEM_DECAY 0.996
#define WUTR_GAIN 1.0
#define WUTR_NUM_SOURCES 10.0
#define WUTR_CENTER_FREQ0 450.0
#define WUTR_CENTER_FREQ1 600.0
#define WUTR_CENTER_FREQ2 750.0
#define WUTR_RESON 0.9985
#define WUTR_FREQ_SWEEP 1.0001
#define MAX_SHAKE 2000
#define THERMAL (0.000025) /* (1.0 / 40000.0) transistor thermal voltage  */
#define ROOT2 (1.4142135623730950488)
#define DEFAULT_SRATE   44100.0
#define MIN_SRATE       5000.0
#define MAX_SRATE       1000000.0
#define MAX_PITCHMOD    20.0
#define DELAYPOS_SHIFT  28
#define DELAYPOS_SCALE  0x10000000
#define DELAYPOS_MASK   0x0FFFFFFF
#define SP_ALSABUFSIZE 4096
