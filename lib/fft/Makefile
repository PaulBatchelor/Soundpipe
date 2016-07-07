LPATHS += $(INTERMEDIATES_PREFIX)/lib/fft/fft.o
UTIL += $(INTERMEDIATES_PREFIX)/lib/fft/fft.c

$(INTERMEDIATES_PREFIX)/lib/fft:
	mkdir -p $@

$(INTERMEDIATES_PREFIX)/lib/fft/fft.c: lib/fft/fftlib.c lib/fft/sp_fft.c | $(INTERMEDIATES_PREFIX)/lib/fft
	echo "/* THIS IS A GENERATED FILE. DO NOT EDIT BY HAND */" > $@
	cat $^ >> $@

$(INTERMEDIATES_PREFIX)/lib/fft/fft.o: $(INTERMEDIATES_PREFIX)/lib/fft/fft.c | $(INTERMEDIATES_PREFIX)/lib/fft
	$(CC) $< -c $(CFLAGS) -o $@
