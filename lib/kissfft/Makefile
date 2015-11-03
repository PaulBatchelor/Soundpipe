LPATHS += lib/kissfft/kiss_fft.o lib/kissfft/kiss_fftr.o
CFLAGS += -Ilib/kissfft/ -Dkiss_fft_scalar=float

lib/kissfft/kiss_fft.o: lib/kissfft/kiss_fft.c
	$(CC) $< -c $(CFLAGS) -o $@

lib/kissfft/kiss_fftr.o: lib/kissfft/kiss_fftr.c
	$(CC) $< -c $(CFLAGS) -o $@
