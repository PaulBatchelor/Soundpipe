default: libsoundpipe.a

include config.mk

VERSION=0.1.1

MPATHS=$(addprefix modules/, $(addsuffix .o, $(MODULES)))
HPATHS=$(addprefix h/, $(addsuffix .h, $(MODULES)))

CFLAGS +=  -g --std=c99 -DSP_VERSION=$(VERSION)

include test/Makefile

modules/%.o: modules/%.c h/%.h modules/base.o h/soundpipe.h
	gcc -Wall $(CFLAGS) -c -static -Ih $< -o $@ 

modules/base.o: modules/base.c 
	gcc -Wall $(CFLAGS) -c -static -Ih $< -o $@ 

h/soundpipe.h: $(HPATHS)
	cat $(HPATHS) > $@

libsoundpipe.a: $(MPATHS)
	ar rcs $@ $^

install: libsoundpipe.a h/soundpipe.h
	install h/soundpipe.h /usr/local/include/
	install libsoundpipe.a /usr/local/lib/

clean: 
	rm -rf gen_noise libsoundpipe.a $(MPATHS) h/soundpipe.h
