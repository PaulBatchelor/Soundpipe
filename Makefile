.PHONY: docs bootstrap all

#default: config.mk libsoundpipe.a

default: all

ifndef CONFIG
CONFIG=config.mk
endif

include $(CONFIG)

VERSION=0.4

MPATHS=$(addprefix modules/, $(addsuffix .o, $(MODULES)))
HPATHS=$(addprefix h/, $(addsuffix .h, $(MODULES)))
CPATHS=$(addprefix modules/, $(addsuffix .c, $(MODULES)))

CFLAGS +=  -g --std=c99 -DSP_VERSION=$(VERSION) -O3
UTIL += util/wav2smp

modules/%.o: modules/%.c h/%.h h/soundpipe.h
	$(CC) -Wall $(CFLAGS) -c -static -Ih $< -o $@

h/soundpipe.h: $(HPATHS)
	cat $(HPATHS) > $@

libsoundpipe.a: $(MPATHS) $(LPATHS)
	ar rcs $@ $(MPATHS) $(LPATHS)

soundpipe.o: $(MPATHS) $(LPATHS)
	ld -shared -fPIC -o $@ $(MPATHS) $(LPATHS)

config.mk: config.def.mk
	cp config.def.mk config.mk

all: config.mk libsoundpipe.a $(UTIL) sp_dict.lua

install: libsoundpipe.a h/soundpipe.h
	install h/soundpipe.h /usr/local/include/
	install libsoundpipe.a /usr/local/lib/

sp_dict.lua:
	cat modules/data/*.lua > sp_dict.lua

clean:
	rm -rf gen_noise libsoundpipe.a $(MPATHS) h/soundpipe.h docs soundpipe.c
	rm -rf $(LPATHS)
	rm -rf $(UTIL)
	rm -rf sp_dict.lua
	rm -rf soundpipe.o

docs:
	util/gendocs.sh

bootstrap:
	util/module_bootstrap.sh $(MODULE_NAME)

util/wav2smp: util/wav2smp.c
	$(CC) $(CFLAGS) $< -lsndfile -o $@

