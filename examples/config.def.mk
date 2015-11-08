files = ex_buthp ex_butlp ex_moogladder ex_noise ex_revsc ex_tone ex_osc \
	ex_wtosc ex_posc3 ex_randi ex_music ex_tevent ex_metro ex_tenv \
	ex_maygate ex_fofilt ex_biquad ex_tbvcf ex_mode ex_reverse ex_dtrig \
	ex_tseq ex_rpt ex_dust ex_port ex_vdelay ex_gen_sinesum ex_music2 \
	ex_streson ex_multichan ex_gen_line ex_bal ex_drip ex_clip ex_butbp \
	ex_music3 ex_fosc ex_dist ex_gbuzz ex_jitter ex_lpf18 ex_music4 \
	ex_gen_xline ex_gen_gauss ex_allpass ex_comb ex_gen_vals ex_phasor ex_tabread \
	ex_music5 ex_eqfil ex_foo ex_butbr ex_in ex_diskin ex_nsmp ex_prop \
	ex_samphold ex_delay ex_switch ex_random ex_dmetro ex_pluck ex_atone ex_tin \
	ex_scale ex_pan2 ex_jcrev ex_tenv2 ex_fold ex_bitcrush ex_inverse ex_mul \
	ex_add ex_sub ex_div ex_abs ex_panst ex_bar ex_progress ex_pareq ex_mincer \
	ex_padsynth

# Jack Module
#
#files += extra/ex_jack
#extra/ex_jack: extra/ex_jack.c
#	gcc -g --std=c99 -I ../h $< ../libsoundpipe.a -lsndfile -ljack -laaio -o $@ -lm

# RPI Module
#
#files += extra/ex_rpi
#extra/ex_rpi: extra/ex_rpi.c
#	gcc -g --std=c99 -I ../h $< ../libsoundpipe.a -lsndfile -lasound -o $@ -lm

#files += extra/ex_rpi_v2
#extra/ex_rpi_v2: extra/ex_rpi_v2.c
#	gcc -g --std=c99 -I ../h $< ../libsoundpipe.a -lsndfile -lasound -o $@ -lm

# Padsynth Module
#
#files += extra/ex_padsynth
#extra/ex_padsynth: extra/ex_padsynth.c
#	gcc -g --std=c99 -I ../h $< ../libsoundpipe.a -lsndfile -lfftw3 -o $@ -lm
