LPATHS += $(INTERMEDIATES_PREFIX)/lib/inih/ini.o
CFLAGS += -Ilib/inih/

$(INTERMEDIATES_PREFIX)/lib/inih:
	mkdir -p $@

$(INTERMEDIATES_PREFIX)/lib/inih/ini.o: lib/inih/ini.c | $(INTERMEDIATES_PREFIX)/lib/inih
	$(CC) $(CFLAGS) $< -c -o $@
