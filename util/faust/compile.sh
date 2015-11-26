NAME=square
faust -cn $NAME -json -lang c -a sp.c $NAME.dsp -o $NAME.c 
go run parse.go $NAME $NAME.dsp.json >> $NAME.c 
