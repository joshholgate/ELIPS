set terminal postscript eps enhanced colour font ",20"
set output "minphi.eps"

set size square
set xlabel "Bo_P"
set ylabel "-e{/Symbol f}_c / k_BT_e"
set logscale x
set logscale y
set format x "10^{%L}"
set format y "10^{%L}"
set key spacing 1.5
set xrange [0.00008:1.8]
set yrange [2:4000]

f(x) = a*x**(-b)
fit f(x) 'minima.dat' u 1:3 via a,b

set label 'Stable' at 0.001,20 front font ",32"
set label 'Unstable' at 0.01,500 front font ",32"

plot 'minima.dat' u 1:3 w l lw 2 dt 1 lc rgb "black" t 'Theory',\
     (x<0.7 ? f(x) : 1/0) w l lw 2 dt 2 lc rgb "black" t '1.72 Bo_P^{-0.784}'

#     'DBD-lims.dat' w filledcurves ls 2 lc rgb "#edb120" t 'DBD',\


#'minima.dat' u 1:3 w filledcurves above x2 lc rgb "#F6CECE" t '', \
#     'minima.dat' u 1:3 w filledcurves below x1 lc rgb "#CEF6CE" t '', \
#     (x<0.7 ? f(x) : 1/0) w l lw 2 dt 2 lc rgb "black" t 'Fit: 1.72 Bo_P^{-0.784}',\
