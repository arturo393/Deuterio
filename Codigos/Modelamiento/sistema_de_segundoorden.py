# -*- coding: latin-1 -*-

import math
import numpy as np 
import matplotlib.pyplot as plt
import numpy as np
from scipy import signal

u0 = 0;  # nivel inicial de entrada en [V]
uf = 12.0; # nivel final de entrada en [V]
y0 = 0;  # nivel inicial de entrada en [A]
yf = 10.0;  # nivel final de salida en [A]
A1 = 30.0; # Amplitud del primer pico en [A]
An = 7.0;  # Amplitud del pico N n en [A]
Tw = 1e-6; # Tiempo entre dos picos sucesivos [s]
n = 2 ;   # numero del segundo pico

tmp = 1/(n-1)*np.log(A1/An)
psi = tmp/np.square(4*np.pi**2 + tmp**2)
Tn = (Tw/2*np.pi)*np.square(1-psi**2)
K = (yf-y0)/(uf-u0)
Wn = 1/Tn;

print 'Factor de amortiguamiento psi=',psi
print "Frecuencia natural Wn=",Wn*1e-6, "[MHz]"
print "Ganancia K=", K

sys2 = signal.lti(K, [Tn**2, 2*psi*Tn, 1]) # H(s) = (s + 2) / (s ** 2 + 6 * s + 25)

w, mag, phase = signal.bode(sys2) # Diagrama de bode: frecuencias, magnitud y fase
fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(6, 6))
ax1.semilogx(w, mag) # Eje x logarítmico
ax2.semilogx(w, phase) # Eje x logarítmico

w, H = signal.freqresp(sys2)
fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(8, 4))
ax1.plot(H.real, H.imag)
ax1.plot(H.real, -H.imag)
ax2.plot(sys2.zeros.real, sys2.zeros.imag, 'o')
ax2.plot(sys2.poles.real, sys2.poles.imag, 'x')

plt.show()