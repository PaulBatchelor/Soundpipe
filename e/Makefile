.PHONY: default clean all
files = ex_buthp ex_butlp ex_moogladder ex_noise ex_revsc ex_tone ex_osc \
		ex_wtosc ex_posc3 ex_randi ex_music ex_tevent ex_metro ex_tenv \
        ex_maygate ex_fofilt ex_biquad ex_tbvcf

default: all

# Jack Module
#
#files += extra/ex_jack
#extra/ex_jack: extra/ex_jack.c
#	gcc -g --std=c99 -I ../h $< ../libsoundpipe.a -lsndfile -ljack -laaio -o $@ -lm

# RPI Module

files += extra/ex_rpi 
extra/ex_rpi: extra/ex_rpi.c
	gcc -g --std=c99 -I ../h $< ../libsoundpipe.a -lsndfile -lasound -o $@ -lm

files += extra/ex_rpi_v2
extra/ex_rpi_v2: extra/ex_rpi_v2.c
	gcc -g --std=c99 -I ../h $< ../libsoundpipe.a -lsndfile -lasound -o $@ -lm

all: $(files)

% :: %.c 
	gcc -g --std=c99 -I ../h $< ../libsoundpipe.a -lsndfile -o $@ -lm

clean:
	rm  -rf $(files) test.wav
