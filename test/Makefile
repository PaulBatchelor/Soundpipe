TESTS=test event ftbl
TPATHS=$(addprefix test/, $(TESTS))

.PHONY: tests

tests: $(TPATHS)

test/libtap.o: test/libtap.c
	gcc -I h/ -c t/libtap.c -o t/libtap.o

test/%: test/%.c test/libtap.o $(MPATHS)
	gcc -g -I h/ $(CFLAGS) -o $@ $< test/libtap.o $(MPATHS)

clean_tests:
	rm -rf $(TPATHS) test/libtap.o
