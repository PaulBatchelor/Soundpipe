LPATHS += $(LIBDIR)/tinywav/tinywav.o
CFLAGS += -Ilib/tinywav/

$(LIBDIR)/tinywav:
	mkdir -p $@

$(LIBDIR)/tinywav/tinywav.o: lib/tinywav/tinywav.c | $(LIBDIR)/tinywav
	$(CC) $(CFLAGS) $< -c -o $@
