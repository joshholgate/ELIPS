set terminal postscript eps enhanced colour font ",20"
set output "minphi.eps"

set size square
set xlabel "Bo_P"
set ylabel "-e{/Symbol f}_c / k_BT_e"
set logscale x
set logscale y
set format x "10^{%L}"
set format y "10^{%L}"
set key off
set xrange [0.00008:1.8]
set yrange [2:4000]

set label 'Stable' at 0.001,20 front font ",32"
set label 'Unstable' at 0.01,500 front font ",32"

plot 'minima.dat' u 1:3 w filledcurves x2 lc rgb "#ffaaaa" t '',\
     'minima.dat' u 1:3 w filledcurves x1 lc rgb "#90EE90" t '',\
     '' u 1:3 w l lw 2 dt 1 lc rgb "black"
