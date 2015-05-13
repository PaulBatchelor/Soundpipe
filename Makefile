default: libsoundpipe.a

MODULES=event 

MPATHS=$(addprefix m/, $(addsuffix .o, $(MODULES)))

include t/Makefile

m/event.o: m/event.c soundpipe.o 
	gcc -c -static -Ih $< -o $@

soundpipe.o: soundpipe.c
	gcc -c -static $<

libsoundpipe.a: soundpipe.o $(MPATHS)
	ar rcs $@ $^

install: libsoundpipe.a
	install soundpipe.h /usr/local/include/
	install libsoundpipe.a /usr/local/lib/

clean: 
	rm -rf gen_noise libsoundpipe.a soundpipe.o $(MPATHS)
