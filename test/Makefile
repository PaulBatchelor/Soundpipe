.PHONY: clean

ex_test.bin: ex_test.c test.c md5.c
	$(CC) -Wall -g -I../h -I /usr/local/include -L /usr/local/lib libtap.c md5.c test.c ex_test.c -lsndfile -lm ../libsoundpipe.a -o$@ 

clean:
	rm -rf ex_test.bin
