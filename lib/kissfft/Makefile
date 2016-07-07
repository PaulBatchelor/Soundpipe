LPATHS += $(INTERMEDIATES_PREFIX)/lib/kissfft/kiss_fft.o $(INTERMEDIATES_PREFIX)/lib/kissfft/kiss_fftr.o
CFLAGS += -Ilib/kissfft/ -Dkiss_fft_scalar=float

$(INTERMEDIATES_PREFIX)/lib/kissfft:
	mkdir -p $@

$(INTERMEDIATES_PREFIX)/lib/kissfft/kiss_fft.o: lib/kissfft/kiss_fft.c | $(INTERMEDIATES_PREFIX)/lib/kissfft
	$(CC) $< -c $(CFLAGS) -o $@

$(INTERMEDIATES_PREFIX)/lib/kissfft/kiss_fftr.o: lib/kissfft/kiss_fftr.c | $(INTERMEDIATES_PREFIX)/lib/kissfft
	$(CC) $< -c $(CFLAGS) -o $@
