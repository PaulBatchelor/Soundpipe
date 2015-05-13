TESTS=test event
TPATHS=$(addprefix t/, $(TESTS))

.PHONY: tests

tests: $(TPATHS)

t/libtap.o: t/libtap.c
	gcc -I h/ -c t/libtap.c -o t/libtap.o

t/%: t/%.c t/libtap.o $(MPATHS)
	gcc -g -I h/ -o $@ $< t/libtap.o $(MPATHS)

clean_tests:
	rm -rf $(TPATHS) t/libtap.o
