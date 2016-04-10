.PHONY: docs bootstrap all

#default: config.mk libsoundpipe.a

default: all

ifndef CONFIG
CONFIG=config.mk
endif

include $(CONFIG)

SPLIBS = libsoundpipe.a

VERSION=1.1.1

MPATHS=$(addprefix modules/, $(addsuffix .o, $(MODULES)))
HPATHS=$(addprefix h/, $(addsuffix .h, $(MODULES)))
CPATHS=$(addprefix modules/, $(addsuffix .c, $(MODULES)))

CFLAGS +=  -g -DSP_VERSION=$(VERSION) -O3 -DSPFLOAT=float -Ih -I/usr/local/include
UTIL += util/wav2smp

modules/%.o: modules/%.c h/%.h h/soundpipe.h
	$(CC) -Wall $(CFLAGS) -c -static $< -o $@

h/soundpipe.h: $(HPATHS)
	cat $(HPATHS) > $@

libsoundpipe.a: $(MPATHS) $(LPATHS)
	ar rcs $@ $(MPATHS) $(LPATHS)

soundpipe.o: $(MPATHS) $(LPATHS)
	gcc $(CFLAGS) -c -combine $(CPATHS) -o $@

config.mk: config.def.mk
	cp config.def.mk config.mk

all: config.mk $(SPLIBS) $(UTIL) sp_dict.lua 

install: $(SPLIBS) h/soundpipe.h
	install h/soundpipe.h /usr/local/include/
	install $(SPLIBS) /usr/local/lib/

sp_dict.lua:
	cat modules/data/*.lua > sp_dict.lua

clean:
	rm -rf gen_noise libsoundpipe.a $(MPATHS) h/soundpipe.h docs soundpipe.c
	rm -rf $(LPATHS)
	rm -rf $(UTIL)
	rm -rf sp_dict.lua

docs:
	util/gendocs.sh

bootstrap:
	util/module_bootstrap.sh $(MODULE_NAME)

util/wav2smp: util/wav2smp.c
	$(CC) -L/usr/local/lib $< -lsndfile -o $@
