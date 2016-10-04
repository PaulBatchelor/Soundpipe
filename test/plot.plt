set terminal png size 900,400 font ',10'
set bmargin 10 
set output "demo.png"
#set yrange [0:]
set nokey
set style data histogram
unset border
# unset xtics
# set xtics format ""
set xtics rotate 
# set xtics offset 0, graph 0.5
set xtics axis

# plot 'time.log' using 1:xtic(2), \
# 'time.log' using 3 with boxes

plot 'time.log' using 2:xtic(1) with boxes


# reset
# set terminal png size "1000x1000"
# set output "test.png"
# set key at graph 0.24, 0.85 horizontal samplen 0.1
# set style data histogram
# set style histogram cluster gap 1
# set style fill solid border -1
# set boxwidth 0.8
# set xtic rotate by 90 scale 0
# unset ytics
# set y2tics rotate by 90
# set yrange [0:0.35]; set xrange [-0.5:6.5]
# set y2label 'Output' offset -2.5
# set xlabel ' '
# set size 0.6, 1
# set label 1 'Year' at graph 0.5, -0.1 centre rotate by 180
# set label 2 'Nowhere' at graph 0.09, 0.85 left rotate by 90
# set label 3 'Everywhere' at graph 0.2, 0.85 left rotate by 90
# p 'foo.log' u 2 title ' ', '' u ($2/2.0+rand(0)/10.0) title ' ', '' u 0:(0):xticlabel(1) w l title ''
