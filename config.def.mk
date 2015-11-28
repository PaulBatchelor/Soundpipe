# Modules that don't require external libraries go here
MODULES= \
abs \
add \
allpass \
atone \
autowah \
bal \
bar \
base \
biquad \
bitcrush \
butbp \
butbr \
buthp \
butlp \
clip \
comb \
count \
dcblock \
delay \
dist \
div \
dmetro \
drip \
dtrig \
dust \
eqfil \
event \
expon \
fofilt \
fold \
foo \
fosc \
ftbl \
gbuzz \
in \
inverse \
jcrev \
jitter \
line \
lpf18 \
maygate \
metro \
mincer \
mode \
moogladder \
mul \
noise \
osc \
pan2 \
panst \
pareq \
phaser \
phasor \
pinknoise \
pluck \
port \
posc3 \
progress \
prop \
randh \
randi \
randmt \
random \
reverse \
revsc \
rms \
rpt \
samphold \
saw \
scale \
square \
streson \
sub \
switch \
tabread \
tbvcf \
tenv \
tenv2 \
tenvx \
tevent \
tin \
tone \
triangle \
tseq \
vdelay \
zitarev

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

include lib/kissfft/Makefile
MODULES += fftwrapper
MODULES += padsynth
# Uncomment to use FFTW3 instead of kissfft.
# CFLAGS += -lfftw3 -DUSE_FFTW3

# Build dynamic library. Needed for Sporth chugin
CFLAGS += -shared -fPIC
BUILD_DYNAMIC=1
