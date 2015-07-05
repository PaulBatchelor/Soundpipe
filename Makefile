.PHONY: docs

default: libsoundpipe.a

include config.mk

VERSION=0.2.1

MPATHS=$(addprefix modules/, $(addsuffix .o, $(MODULES)))
HPATHS=$(addprefix h/, $(addsuffix .h, $(MODULES)))
CPATHS=$(addprefix modules/, $(addsuffix .c, $(MODULES)))

CFLAGS +=  -g --std=c99 -DSP_VERSION=$(VERSION)

include test/Makefile

modules/%.o: modules/%.c h/%.h h/soundpipe.h
	gcc -Wall $(CFLAGS) -c -static -Ih $< -o $@ 

h/soundpipe.h: $(HPATHS)
	cat $(HPATHS) > $@

libsoundpipe.a: $(MPATHS)
	ar rcs $@ $^

soundpipe.c: $(CPATHS) h/soundpipe.h
	cat $(CPATHS) | sed "/^#/d" > tmp 
	cat util/include.h tmp > soundpipe.c
	rm tmp

install: libsoundpipe.a h/soundpipe.h
	install h/soundpipe.h /usr/local/include/
	install libsoundpipe.a /usr/local/lib/

docs:
	util/gendocs.sh

clean: 
	rm -rf gen_noise libsoundpipe.a $(MPATHS) h/soundpipe.h docs soundpipe.c
