.PHONY: all clean install docs bootstrap util

default: all

VERSION = 1.7.0

INTERMEDIATES_PREFIX ?= .
PREFIX ?= /usr/local

LIBSOUNDPIPE = $(INTERMEDIATES_PREFIX)/libsoundpipe.a
SOUNDPIPEO = $(INTERMEDIATES_PREFIX)/soundpipe.o
MODDIR = $(INTERMEDIATES_PREFIX)/modules
HDIR = $(INTERMEDIATES_PREFIX)/h
UTILDIR = $(INTERMEDIATES_PREFIX)/util
LIBDIR = $(INTERMEDIATES_PREFIX)/lib


ifndef CONFIG
CONFIG = $(INTERMEDIATES_PREFIX)/config.mk
endif

HPATHS += $(addprefix h/, $(addsuffix .h, $(MODULES)))
CPATHS += $(addprefix modules/, $(addsuffix .c, $(MODULES)))
MPATHS += $(addprefix $(MODDIR)/, $(addsuffix .o, $(MODULES)))

include $(CONFIG)

ifeq ($(USE_DOUBLE), 1)
CFLAGS+=-DUSE_DOUBLE
SPFLOAT=double
else
SPFLOAT=float
endif

CFLAGS += -DSP_VERSION=$(VERSION) -O3 -DSPFLOAT=${SPFLOAT} #-std=c99
CFLAGS += -I$(INTERMEDIATES_PREFIX)/h -Ih -I/usr/local/include -fPIC
UTIL += $(INTERMEDIATES_PREFIX)/util/wav2smp

$(INTERMEDIATES_PREFIX) \
$(INTERMEDIATES_PREFIX)/h \
$(INTERMEDIATES_PREFIX)/modules \
$(INTERMEDIATES_PREFIX)/util \
$(PREFIX)/include \
$(PREFIX)/lib \
$(PREFIX)/share/doc/soundpipe:
	mkdir -p $@

$(LIBSOUNDPIPE): $(MPATHS) $(LPATHS) | $(INTERMEDIATES_PREFIX)
	$(AR) rcs $@ $(MPATHS) $(LPATHS)

$(HDIR)/soundpipe.h: $(HPATHS) | $(INTERMEDIATES_PREFIX)/h
	echo "#ifndef SOUNDPIPE_H" >> $@
ifdef USE_DOUBLE
	echo "#define USE_DOUBLE" >> $@
endif
	echo "#define SOUNDPIPE_H" >> $@
	cat $(HPATHS) >> $@
	echo "#endif" >> $@

$(HDIR)/sp_base.h: h/base.h 
	>$@
	echo "#ifndef SOUNDPIPE_H" >> $@
ifdef USE_DOUBLE
	echo "#define USE_DOUBLE" >> $@
endif
	echo "#define SOUNDPIPE_H" >> $@
	cat $< >> $@
	echo "#endif" >> $@

$(MODDIR)/%.o: modules/%.c h/%.h $(HDIR)/soundpipe.h | $(MODDIR)
	$(CC) -Wall $(CFLAGS) -c -static $< -o $@

$(SOUNDPIPEO): $(MPATHS) $(LPATHS) | $(INTERMEDIATES_PREFIX)
	$(CC) $(CFLAGS) -c -combine $(CPATHS) -o $@

$(INTERMEDIATES_PREFIX)/config.mk: config.def.mk | $(INTERMEDIATES_PREFIX)
	cp $< $@

$(UTILDIR)/wav2smp: util/wav2smp.c | $(UTILDIR)
	$(CC) $(CFLAGS) -L/usr/local/lib $< -lsndfile -o $@

stretcher: $(UTILDIR)/stretcher

$(UTILDIR)/stretcher: util/stretcher.c | $(UTILDIR)
	$(CC) $(CFLAGS) -L/usr/local/lib $< -L. -lsoundpipe -lsndfile -lm -o $@

$(INTERMEDIATES_PREFIX)/sp_dict.lua: | $(INTERMEDIATES_PREFIX)
	cat modules/data/*.lua > $@

bootstrap:
	util/module_bootstrap.sh $(MODULE_NAME)

docs:
	export INTERMEDIATES_PREFIX=$(INTERMEDIATES_PREFIX) && util/gendocs.sh

all: $(INTERMEDIATES_PREFIX)/config.mk \
	$(INTERMEDIATES_PREFIX)/libsoundpipe.a \
	$(INTERMEDIATES_PREFIX)/sp_dict.lua \
	$(HDIR)/sp_base.h

util: $(UTIL)

install: \
	$(INTERMEDIATES_PREFIX)/h/soundpipe.h \
	$(INTERMEDIATES_PREFIX)/h/sp_base.h \
	$(INTERMEDIATES_PREFIX)/libsoundpipe.a | \
		$(PREFIX)/include \
		$(PREFIX)/lib
	install $(HDIR)/soundpipe.h $(PREFIX)/include/
	install $(HDIR)/sp_base.h $(PREFIX)/include/
	install $(LIBSOUNDPIPE) $(PREFIX)/lib/

clean:
	rm -rf $(HDIR)/soundpipe.h
	rm -rf $(INTERMEDIATES_PREFIX)/docs
	rm -rf $(INTERMEDIATES_PREFIX)/gen_noise
	rm -rf $(INTERMEDIATES_PREFIX)/libsoundpipe.a
	rm -rf $(INTERMEDIATES_PREFIX)/soundpipe.c
	rm -rf $(INTERMEDIATES_PREFIX)/sp_dict.lua
	rm -rf $(LPATHS)
	rm -rf $(MPATHS)
	rm -rf $(UTIL)
	rm -rf $(UTILDIR)/wav2smp.dSYM
	rm -rf $(HDIR)/sp_base.h
