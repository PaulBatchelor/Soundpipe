.PHONY: default clean
files = ex_buthp ex_butlp ex_moogladder ex_noise ex_revsc ex_tone ex_osc \
		ex_wtosc ex_posc3 ex_randi ex_music ex_tevent

default: $(files)

% :: %.c 
	gcc -O3 -g -I ../h $< ../libsoundpipe.a -lsndfile -o $@ -lm

clean:
	rm  -rf $(files) test.wav
