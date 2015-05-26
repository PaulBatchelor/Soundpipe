gcc -g -I ../h ex_noise.c ../libsoundpipe.a -lsndfile -o ex_noise
gcc -g -I ../h ex_tone.c ../libsoundpipe.a -lsndfile -o ex_tone -lm
gcc -g -I ../h ex_moogladder.c ../libsoundpipe.a -lsndfile -o ex_moogladder -lm
