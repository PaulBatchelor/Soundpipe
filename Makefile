.PHONY: docs bootstrap all

#default: config.mk libsoundpipe.a

default: all

include config.mk

VERSION=0.3

MPATHS=$(addprefix modules/, $(addsuffix .o, $(MODULES)))
HPATHS=$(addprefix h/, $(addsuffix .h, $(MODULES)))
CPATHS=$(addprefix modules/, $(addsuffix .c, $(MODULES)))

CFLAGS +=  -g --std=c99 -DSP_VERSION=$(VERSION)

UTIL += util/wav2smp

include test/Makefile

modules/%.o: modules/%.c h/%.h h/soundpipe.h
	gcc -Wall $(CFLAGS) -c -static -Ih $< -o $@ 

h/soundpipe.h: $(HPATHS)
	cat $(HPATHS) > $@

libsoundpipe.a: $(MPATHS) $(LPATHS)
	ar rcs $@ $(MPATHS) $(LPATHS)

config.mk: config.def.mk
	cp config.def.mk config.mk

soundpipe.c: $(CPATHS) h/soundpipe.h 
	cat $(CPATHS) | sed "/^#/d" > tmp 
	cat util/include.h tmp > soundpipe.c
	rm tmp

all: config.mk libsoundpipe.a $(UTIL)

install: libsoundpipe.a h/soundpipe.h
	install h/soundpipe.h /usr/local/include/
	install libsoundpipe.a /usr/local/lib/

clean: 
	rm -rf gen_noise libsoundpipe.a $(MPATHS) h/soundpipe.h docs soundpipe.c
	rm -rf $(LPATHS)
	rm -rf $(UTIL)

docs:
	util/gendocs.sh

bootstrap: 
	util/module_bootstrap.sh $(MODULE_NAME)

util/wav2smp: util/wav2smp.c
	gcc $< -lsndfile -o $@

