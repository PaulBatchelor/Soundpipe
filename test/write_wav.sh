#/bin/sh

cat *.raw | sox -t raw -c 1 -r 44100 -e floating-point -b 32 - out.wav

