LPATHS += $(INTERMEDIATES_PREFIX)/lib/spa/spa.o
CFLAGS += -Ilib/spa/
HPATHS += lib/spa/spa.h

$(INTERMEDIATES_PREFIX)/lib/spa:
	mkdir -p $@

$(INTERMEDIATES_PREFIX)/lib/spa/spa.o: lib/spa/spa.c | $(INTERMEDIATES_PREFIX)/lib/spa
	gcc $(CFLAGS) $< -c -o $@
