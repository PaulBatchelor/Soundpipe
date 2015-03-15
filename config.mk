# Modules that don't require external libraries go here
MODULES=base event noise tone moogladder butter revsc ftbl osc posc3 randi \
	dcblock tevent metro tenv maygate fofilt biquad tbvcf mode reverse \
	dtrig rpt dust port del count streson tseq bal drip clip fosc dist \
	gbuzz

# JACK module
#
#MODULES += jack
#CFLAGS += -ljack

# RPi Module
#
MODULES += rpi
CFLAGS += -lasound

# Padsynth module
#
#MODULES += fftwrapper 
#MODULES += padsynth
#CFLAGS += -lfftw3


