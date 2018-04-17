# Modules that don't require external libraries go here
MODULES= \
base \
ftbl \
tevent \
adsr \
allpass \
atone \
autowah \
bal \
bar \
biquad \
biscale \
blsaw \
blsquare \
bltriangle \
fold \
bitcrush \
brown \
butbp \
butbr \
buthp \
butlp \
clip \
clock \
comb \
compressor \
count \
conv \
crossfade \
dcblock \
delay \
diode \
dist \
dmetro \
drip \
dtrig \
dust \
eqfil \
expon \
fof \
fog \
fofilt \
foo \
fosc \
gbuzz \
hilbert \
in \
incr \
jcrev \
jitter \
line \
lpc \
lpf18 \
maygate \
metro \
mincer \
mode \
moogladder \
noise \
nsmp \
osc \
oscmorph \
pan2 \
panst \
pareq \
paulstretch \
pdhalf \
peaklim \
phaser \
phasor \
pinknoise \
pitchamdf \
pluck \
port \
posc3 \
progress \
prop \
pshift \
ptrack \
randh \
randi \
randmt \
random \
reverse \
reson \
revsc \
rms \
rpt \
rspline \
saturator \
samphold \
scale \
scrambler \
sdelay \
slice \
smoothdelay \
spa \
sparec \
streson \
switch \
tabread \
tadsr \
talkbox \
tblrec \
tbvcf \
tdiv \
tenv \
tenv2 \
tenvx \
tgate \
thresh \
timer \
tin \
tone \
trand \
tseg \
tseq \
vdelay \
voc \
vocoder \
waveset \
wavin \
wavout \
wpkorg35 \
zitarev

ifndef NO_LIBSNDFILE
	MODULES += diskin
else
	CFLAGS += -DNO_LIBSNDFILE
endif

# ini parser needed for nsmp module
include lib/inih/Makefile

# Header files needed for modules generated with FAUST
CFLAGS += -Ilib/faust

# fft library
include lib/fft/Makefile

include lib/kissfft/Makefile
MODULES += fftwrapper
MODULES += padsynth

# Uncomment to use FFTW3 instead of kissfft.
# CFLAGS += -DUSE_FFTW3

# Soundpipe audio
include lib/spa/Makefile

# openlpc
include lib/openlpc/Makefile

# drwav
include lib/dr_wav/Makefile

CFLAGS += -fPIC -g

# Uncomment this to use double precision
#USE_DOUBLE=1
