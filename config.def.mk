# Modules that don't require external libraries go here
MODULES=base event noise tone moogladder butter revsc ftbl osc posc3 randi \
	dcblock tevent metro tenv maygate fofilt biquad tbvcf mode reverse \
	dtrig rpt dust port vdelay count streson tseq bal drip clip fosc dist \
	gbuzz rms jitter lpf18 randmt allpass comb phasor tabread vco \
	eqfil foo butbr in diskin nsmp prop samphold delay switch dmetro random \
	pluck atone tin scale pan2 jcrev tenv2 fold decimator inverse mul add sub \
  div abs panst


# ini parser needed for nsmp module
include lib/inih/Makefile

# Header files needed for modules generated with FAUST
CFLAGS += -I lib/faust

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

# If you are on OSX, you may need this 
# CFLAGS += -I /usr/local/include -L /usr/local/include
