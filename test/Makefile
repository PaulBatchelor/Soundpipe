.PHONY: clean

all: libsptest.a run.bin

tests = \
t_allpass \
t_atone \
t_bal \
t_biquad \
t_biscale \
t_bitcrush \
t_blsaw \
t_blsquare \
t_bltriangle \
t_butbp \
t_butbr \
t_buthp \
t_butlp \
t_clip \
t_comb \
t_delay \
t_dist \
t_dmetro \
t_drip \
t_dtrig \
t_dust \
t_eqfil \
t_expon \
t_fofilt \
t_fold \
t_foo \
t_fosc \
t_gbuzz \
t_gen_gauss \
t_gen_line \
t_gen_sine \
t_gen_sinesum \
t_gen_vals \
t_gen_xline \
t_jcrev \
t_jitter \
t_line \
t_lpf18 \
t_maygate \
t_mode \
t_moogladder \
t_noise \
t_osc \
t_pareq \
t_phasor \
t_pluck \
t_port \
t_posc3 \
t_prop \
t_randh \
t_randi \
t_random \
t_reverse \
t_revsc \
t_rpt \
t_samphold \
t_scale \
t_streson \
t_tbvcf \
t_tenv \
t_tenv2 \
t_tone \
t_trand \
t_tseq \
t_vdelay

OBJ = $(addprefix t/, $(addsuffix .o, $(tests)))

LDFLAGS += -L/usr/local/lib -lsndfile -lm
CFLAGS += -g -I../h -I /usr/local/include -I. -O3 -Wall -Werror

ifdef WRITE_RAW
CFLAGS += -DWRITE_RAW
endif

libsptest.a: md5.o test.o libtap.o
	ld -o $@ -r md5.o libtap.o test.o

t/%.o: t/%.c
	$(CC) -c $(CFLAGS) -o $@ $<

test.o: test.c
	$(CC) -g -I../h -I /usr/local/include -c -o $@ $<

run.bin: run.c test.c md5.c libsptest.a $(OBJ) all_tests.h
	$(CC) run.c -Wall $(CFLAGS) $(LDFLAGS) -o$@ $(OBJ) ../libsoundpipe.a libsptest.a

clean:
	rm -rf run.bin libsptest.a *.o $(OBJ) *.raw
