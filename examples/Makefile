.PHONY: default clean all

default: all

config.mk: config.def.mk
	cp config.def.mk config.mk

include config.mk


all: config.mk $(addsuffix .bin, $(files)) 

%.bin : %.c 
	gcc -g --std=c99 -I ../h $< ../libsoundpipe.a -lsndfile -o $@ -lm

clean:
	rm  -rf $(addsuffix .bin, $(files)) test.wav plot.dat plot.png
