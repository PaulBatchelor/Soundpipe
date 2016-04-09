LPATHS += lib/fft/fft.o 
UTIL += lib/fft/fft.c
lib/fft/fft.c: lib/fft/fftlib.c lib/fft/sp_fft.c
	echo "/* THIS IS A GENERATED FILE. DO NOT EDIT BY HAND */\n\n\n\n\n" > $@
	cat $^ >> $@

lib/fft/fft.o: lib/fft/fft.c
	$(CC) $< -c $(CFLAGS) -o $@
