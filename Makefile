default: libsoundpipe.a

soundpipe.o: soundpipe.c
	gcc -c $<
libsoundpipe.a: soundpipe.o
	ar -rcs $@ $<
gen_noise: gen_noise.c
	gcc -o $@ -lsndfile $< libsoundpipe.a
clean: 
	rm -rf gen_noise libsoundpipe.a soundpipe.o
