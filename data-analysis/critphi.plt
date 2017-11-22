set terminal postscript eps enhanced colour font ",20"
set output "critphi.eps"

set size square
set key at 100,1000
set key spacing 1.5
set xlabel "k{/Symbol l}_D"
set ylabel "-e{/Symbol f}_c / k_BT_e"
set key title "Bo_P"
set logscale x
set logscale y
set format y "10^{%L}"
set xrange [0.002:7]
set yrange [1:10000]

plot 'Bond0.0001.dat' u (sqrt($1)):2 w lp lw 2 lc rgb "#77ac30" lt 6 t '10^{-4}',\
     -0.5*(1-(2+0.5*x/0.0001)**2) lw 2 dt 2 lc rgb "#77ac30" t '',\
     'Bond0.001.dat' u (sqrt($1)):2 w lp lw 2 lc rgb "#7e2f8e" lt 7 t '10^{-3}',\
     -0.5*(1-(2+0.5*x/0.001)**2) lw 2 dt 2 lc rgb "#7e2f8e" t '',\
     'Bond0.01.dat' u (sqrt($1)):2 w lp lw 2 lc rgb "#edb120" lt 4 t '10^{-2}',\
     -0.5*(1-(2+0.5*x/0.01)**2) lw 2 dt 2 lc rgb "#edb120" t '',\
     'Bond0.1.dat' u (sqrt($1)):2 w lp lw 2 lc rgb "#d95319" pt 5 t '10^{-1}',\
     -0.5*(1-(2+0.5*x/0.1)**2) lw 2 dt 2 lc rgb "#d95319" t '',\
     'Bond1.dat' u (sqrt($1)):2 w lp lw 2 lc rgb "#4dbeee" pt 8 t '10^0',\
     -0.5*(1-(2+0.5*x/1)**2) lw 2 dt 2 lc rgb "#4dbeee" t ''
#     'minima.dat' u (sqrt($2)):3 w l lw 2 dt 1 lc rgb "black" t '' smooth bezier
