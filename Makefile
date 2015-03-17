default: libsoundpipe.a

soundpipe.o: soundpipe.c
	gcc -c $<
libsoundpipe.a: soundpipe.o
	ar rcs $@ $<

install: libsoundpipe.a
	install soundpipe.h /usr/local/include/
	install libsoundpipe.a /usr/local/lib/
clean: 
	rm -rf gen_noise libsoundpipe.a soundpipe.o
