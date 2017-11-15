CFLAGS += -Ilib/dr_wav/
LPATHS += $(LIBDIR)/dr_wav/dr_wav.o

$(LIBDIR)/dr_wav/dr_wav.o: lib/dr_wav/dr_wav.c | $(LIBDIR)/dr_wav
	$(CC) $(CFLAGS) $< -c -o $@
