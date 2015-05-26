default: libsoundpipe.a

MODULES=base event noise

MPATHS=$(addprefix m/, $(addsuffix .o, $(MODULES)))
HPATHS=$(addprefix h/, $(addsuffix .h, $(MODULES)))

include t/Makefile

m/%.o: m/%.c h/%.h m/base.o h/soundpipe.h
	gcc -Wall -lsndfile -g -c -static -Ih $< -o $@ 

#m/event.o: m/event.c h/event.h m/base.o h/soundpipe.h
#	gcc -Wall -lsndfile -g -c -static -Ih $< -o $@ 
#
m/base.o: m/base.c 
	gcc -Wall -g -c -static -lsndfile -Ih $< -o $@ 

h/soundpipe.h: $(HPATHS)
	cat $(HPATHS) > $@

libsoundpipe.a: $(MPATHS)
	ar rcs $@ $^

install: libsoundpipe.a h/soundpipe.h
	install h/soundpipe.h /usr/local/include/
	install libsoundpipe.a /usr/local/lib/

clean: 
	rm -rf gen_noise libsoundpipe.a $(MPATHS) h/soundpipe.h
