gcc -g -I ../h ex_noise.c ../libsoundpipe.a -lsndfile -o ex_noise
gcc -g -I ../h ex_tone.c ../libsoundpipe.a -lsndfile -o ex_tone -lm
gcc -g -I ../h ex_moogladder.c ../libsoundpipe.a -lsndfile -o ex_moogladder -lm
gcc -g -I ../h ex_butlp.c ../libsoundpipe.a -lsndfile -o ex_butlp -lm
gcc -g -I ../h ex_buthp.c ../libsoundpipe.a -lsndfile -o ex_buthp -lm
