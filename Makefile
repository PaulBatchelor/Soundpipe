.PHONY: all bootstrap clean docs install

default: all

VERSION = 1.2.6

INTERMEDIATES_PREFIX ?= .
PREFIX ?= /usr/local

ifndef CONFIG
CONFIG = $(INTERMEDIATES_PREFIX)/config.mk
endif

HPATHS += $(addprefix h/, $(addsuffix .h, $(MODULES)))
CPATHS += $(addprefix modules/, $(addsuffix .c, $(MODULES)))
MPATHS += $(addprefix $(INTERMEDIATES_PREFIX)/modules/, $(addsuffix .o, $(MODULES)))

include $(CONFIG)

CFLAGS += -g -DSP_VERSION=$(VERSION) -O0 -DSPFLOAT=float -I$(INTERMEDIATES_PREFIX)/h -Ih -I/usr/local/include
UTIL += $(INTERMEDIATES_PREFIX)/util/wav2smp

$(INTERMEDIATES_PREFIX) \
$(INTERMEDIATES_PREFIX)/h \
$(INTERMEDIATES_PREFIX)/modules \
$(INTERMEDIATES_PREFIX)/util \
$(PREFIX)/include \
$(PREFIX)/lib \
$(PREFIX)/share/doc/soundpipe:
	mkdir -p $@

$(INTERMEDIATES_PREFIX)/libsoundpipe.a: $(MPATHS) $(LPATHS) | $(INTERMEDIATES_PREFIX)
	$(AR) rcs $@ $(MPATHS) $(LPATHS)

$(INTERMEDIATES_PREFIX)/h/soundpipe.h: $(HPATHS) | $(INTERMEDIATES_PREFIX)/h
	cat $(HPATHS) > $@

$(INTERMEDIATES_PREFIX)/modules/%.o: modules/%.c h/%.h $(INTERMEDIATES_PREFIX)/h/soundpipe.h | $(INTERMEDIATES_PREFIX)/modules
	$(CC) -Wall $(CFLAGS) -c -static $< -o $@

$(INTERMEDIATES_PREFIX)/soundpipe.o: $(MPATHS) $(LPATHS) | $(INTERMEDIATES_PREFIX)
	$(CC) $(CFLAGS) -c -combine $(CPATHS) -o $@

$(INTERMEDIATES_PREFIX)/config.mk: config.def.mk | $(INTERMEDIATES_PREFIX)
	cp config.def.mk $@

$(INTERMEDIATES_PREFIX)/util/wav2smp: util/wav2smp.c | $(INTERMEDIATES_PREFIX)/util
	$(CC) $(CFLAGS) -L/usr/local/lib $< -lsndfile -o $@

$(INTERMEDIATES_PREFIX)/sp_dict.lua: | $(INTERMEDIATES_PREFIX)
	cat modules/data/*.lua > $@

bootstrap:
	export PREFIX=$(PREFIX) INTERMEDIATES_PREFIX=$(INTERMEDIATES_PREFIX) && util/module_bootstrap.sh $(MODULE_NAME)

docs:
	export INTERMEDIATES_PREFIX=$(INTERMEDIATES_PREFIX) && util/gendocs.sh

all: \
  $(INTERMEDIATES_PREFIX)/config.mk \
  $(INTERMEDIATES_PREFIX)/libsoundpipe.a \
  $(INTERMEDIATES_PREFIX)/sp_dict.lua \
  $(UTIL) \
  docs

install: \
  $(INTERMEDIATES_PREFIX)/h/soundpipe.h \
  $(INTERMEDIATES_PREFIX)/libsoundpipe.a \
  docs | \
    $(PREFIX)/include \
    $(PREFIX)/lib \
    $(PREFIX)/share/doc/soundpipe
	install $(INTERMEDIATES_PREFIX)/h/soundpipe.h $(PREFIX)/include/
	install $(INTERMEDIATES_PREFIX)/libsoundpipe.a $(PREFIX)/lib/
	cp -a $(INTERMEDIATES_PREFIX)/docs/* $(PREFIX)/share/doc/soundpipe

clean:
	rm -rf $(INTERMEDIATES_PREFIX)/config.mk
	rm -rf $(INTERMEDIATES_PREFIX)/docs
	rm -rf $(INTERMEDIATES_PREFIX)/gen_noise
	rm -rf $(INTERMEDIATES_PREFIX)/h/soundpipe.h
	rm -rf $(INTERMEDIATES_PREFIX)/libsoundpipe.a
	rm -rf $(INTERMEDIATES_PREFIX)/sp_dict.lua
	rm -rf $(INTERMEDIATES_PREFIX)/soundpipe.c
	rm -rf $(INTERMEDIATES_PREFIX)/util/wav2smp.dSYM
	rm -rf $(MPATHS)
	rm -rf $(LPATHS)
	rm -rf $(UTIL)
