files = \
ex_adsr \
ex_allpass \
ex_atone \
ex_autowah \
ex_bal \
ex_bar \
ex_biquad \
ex_biscale \
ex_bitcrush \
ex_blsaw \
ex_blsquare \
ex_bltriangle \
ex_brown \
ex_butbp \
ex_butbr \
ex_buthp \
ex_butlp \
ex_clamp \
ex_clip \
ex_clock \
ex_comb \
ex_compressor \
ex_conv \
ex_crossfade \
ex_delay \
ex_diskin \
ex_dist \
ex_diode \
ex_dmetro \
ex_drip \
ex_dtrig \
ex_dust \
ex_eqfil \
ex_expon \
ex_fof \
ex_fog \
ex_fofilt \
ex_fold \
ex_foo \
ex_fosc \
ex_gbuzz \
ex_gen_composite \
ex_gen_gauss \
ex_gen_line \
ex_gen_rand \
ex_gen_sine \
ex_gen_sinesum \
ex_gen_triangle \
ex_gen_vals \
ex_gen_xline \
ex_granule \
ex_hilbert \
ex_in \
ex_incr \
ex_jcrev \
ex_jitter \
ex_line \
ex_lpc \
ex_lpf18 \
ex_maygate \
ex_metro \
ex_mincer \
ex_mode \
ex_moogladder \
ex_multichan \
ex_music \
ex_music2 \
ex_music3 \
ex_music4 \
ex_music5 \
ex_noise \
ex_nsmp \
ex_osc \
ex_oscmorph \
ex_padsynth \
ex_pan2 \
ex_panst \
ex_pareq \
ex_paulstretch \
ex_pdhalf \
ex_peaklim \
ex_phaser \
ex_phasor \
ex_pinknoise \
ex_pluck \
ex_port \
ex_posc3 \
ex_progress \
ex_prop \
ex_pshift \
ex_ptrack \
ex_randh \
ex_randi \
ex_random \
ex_reson \
ex_reverse \
ex_revsc \
ex_rpt \
ex_rspline  \
ex_saturator \
ex_samphold \
ex_scale \
ex_scrambler \
ex_streson \
ex_smoothdelay \
ex_sndwarp \
ex_slice \
ex_spa \
ex_sparec \
ex_switch \
ex_tabread \
ex_tadsr \
ex_talkbox \
ex_tblrec \
ex_tbvcf \
ex_tdiv \
ex_tenv \
ex_tenv2 \
ex_tenvx \
ex_tevent \
ex_tgate \
ex_thresh \
ex_timer \
ex_tin \
ex_tone \
ex_trand \
ex_tseq \
ex_tseg \
ex_vdelay \
ex_wtosc \
ex_vocoder \
ex_voc \
ex_voctract \
ex_waveset \
ex_wavout \
ex_wavin \
ex_wpkorg35 \
ex_zitarev

# Padsynth Module
#
#files += extra/ex_padsynth
#extra/ex_padsynth.bin: extra/ex_padsynth.c
#	gcc -g --std=c99 -I ../h $< ../libsoundpipe.a -lsndfile -lfftw3 -o $@ -lm
