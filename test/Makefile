.PHONY: clean

ex_test: ex_test.c test.c md5.c
	$(CC) -Wall -g -I../h libtap.c md5.c test.c ex_test.c -lsndfile -lm ../libsoundpipe.a -o ex_test

clean:
	rm -rf ex_test
