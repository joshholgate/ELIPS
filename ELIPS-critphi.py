# ELIPS-critphi.py
# Extract gradients from ELIPS output to find normalized sheath stress perturbation 
# Then find critical phi value for onset of instability for a given plasma Bond number and wavenumber
# Plot data with gnuplot script 'critphi.plt'

import numpy as np
from scipy.interpolate import interp1d
from scipy import optimize

ksq = [0.000001,0.000002,0.000005,0.00001,0.00002,0.00005,0.0001,0.0002,0.0005,0.001,0.002,0.005,0.01,0.02,0.05,0.1,0.2,0.5,1,2,5,10,20,50]
critphi = []
bond = 1

for i in range(len(ksq)):
  gradients = [-1e-20]
  phi = [0,1,2,5,10,20,50,100,200,500,1000,2000,5000,10000,20000]
  for j in range(len(phi)-1):
    data = np.loadtxt("K"+str(ksq[i])+"/RK4-loopXi-Phi-"+str(phi[j+1])+".dat")
    x = []
    y = []
    for k in range(len(data)):
      x.append(data[k][0])
      y.append(data[k][5])
    def f(x, a):
      return a*x
    a = np.polyfit(x, y, 1)
    gradients.append(a[0]-ksq[i]/bond)
  if (gradients[0]*gradients[len(gradients)-1] > 0):
    critphi.append(20000)
  else:
    f = interp1d(phi, gradients)
    critphi.append(optimize.brentq(f, 0, 20000))

np.savetxt("Bond"+str(bond)+".dat", np.transpose([ksq, critphi]))
