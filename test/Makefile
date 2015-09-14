.PHONY: clean

all: libsptest.a ex_test.bin

libsptest.a: md5.o test.o libtap.o
	ld -o $@ -r md5.o libtap.o test.o 

ex_test.bin: ex_test.c test.c md5.c libsptest.a
	$(CC) -Wall -g -I../h -I /usr/local/include -L /usr/local/lib ex_test.c -lsndfile -lm ../libsoundpipe.a libsptest.a -o$@ 

clean:
	rm -rf ex_test.bin libsptest.a *.o
