FILES= p_moogladder \
	   p_butlp \
	   p_lpf18

default: $(FILES)

p_%: p_%.c
	gcc $< -lsoundpipe -lsndfile -lm -o $@

clean:
	rm -rf $(FILES) times.txt
