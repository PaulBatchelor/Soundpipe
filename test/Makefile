.PHONY: clean

all: libsptest.a run.bin

tests = t_foo t_osc t_allpass t_atone t_bal t_biquad t_butbp t_butbr t_buthp \
		t_butlp t_clip t_comb t_decimator t_delay t_dist t_div t_dmetro t_drip \
		t_dtrig t_dust t_eqfil

OBJ = $(addprefix t/, $(addsuffix .o, $(tests)))

LDFLAGS += -L/usr/local/lib -lsndfile -lm 
CFLAGS += -g -I../h -I /usr/local/include -I. -O3

ifdef WRITE_RAW
CFLAGS += -DWRITE_RAW
endif

libsptest.a: md5.o test.o libtap.o
	ld -o $@ -r md5.o libtap.o test.o

t/%.o: t/%.c
	$(CC) -c $(CFLAGS) -o $@ $< 

test.o: test.c
	$(CC) -I../h -I /usr/local/include -c -o $@ $<

run.bin: run.c test.c md5.c libsptest.a $(OBJ) all_tests.h
	$(CC) run.c -Wall $(CFLAGS) $(LDFLAGS) -o$@ $(OBJ) ../libsoundpipe.a libsptest.a

clean:
	rm -rf run.bin libsptest.a *.o $(OBJ) *.raw
