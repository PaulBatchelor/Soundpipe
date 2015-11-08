# Modules that don't require external libraries go here
MODULES=base event noise tone moogladder revsc ftbl osc posc3 randi \
	dcblock tevent metro tenv maygate fofilt biquad tbvcf mode reverse \
	dtrig rpt dust port vdelay count streson tseq bal drip clip fosc dist \
	gbuzz rms jitter lpf18 randmt allpass comb phasor tabread \
	eqfil foo in prop samphold delay switch dmetro random \
	pluck atone tin scale pan2 jcrev tenv2 fold bitcrush inverse mul add sub \
	div abs panst bar progress pareq butbr butbp buthp butlp mincer

ifndef NO_LIBSNDFILE
	MODULES += nsmp diskin
else
	CFLAGS += -DNO_LIBSNDFILE
endif

# ini parser needed for nsmp module
include lib/inih/Makefile

# Header files needed for modules generated with FAUST
CFLAGS += -I lib/faust

# fft library
include lib/fft/Makefile

# JACK module
#
#MODULES += jack
#CFLAGS += -ljack

# RPi Module
#
#MODULES += rpi
#CFLAGS += -lasound

# Padsynth module
#
#MODULES += fftwrapper
#MODULES += padsynth
#CFLAGS += -lfftw3

# Build dynamic library. Needed for Sporth chugin
# CFLAGS += -shared -fPIC
# BUILD_DYNAMIC=1
