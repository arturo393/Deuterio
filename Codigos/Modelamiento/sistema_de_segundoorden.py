# -*- coding: latin-1 -*-

import math
import numpy as np
import matplotlib.pyplot as plt
import numpy as np
from scipy import signal

u0 = 0;  # nivel inicial de entrada en [V]
uf = 12.0; # nivel final de entrada en [V]
y0 = 0;  # nivel inicial de salida en [A]
yf = 9.82;  # nivel final de salida en [A]
A1 = 11.42-yf; # Amplitud del primer pico en [A]
An = yf-9.71;  # Amplitud del pico N n en [A]
Tw = (1635-1632)*1e-3; # Tiempo entre dos picos sucesivos [s]
n = 3 ;   # numero del segundo pico

tmp = 1/(n-1)*np.log(A1/An)
psi = tmp/np.sqrt(4*np.pi**2 + tmp**2)  # Fixed: was np.square, should be np.sqrt
Tn = (Tw/(2*np.pi))*np.sqrt(1-psi**2)  # Fixed: was np.square, should be np.sqrt
K = (yf-y0)/(uf-u0)
Wn = 1/Tn;

print(f'Factor de amortiguamiento psi = {psi:.6f}')
print(f"Frecuencia natural Wn = {Wn*1e-6:.3f} [MHz]")
print(f"Ganancia K = {K:.4f}")

sys2 = signal.TransferFunction(K, [Tn**2, 2*psi*Tn, 1]) # H(s) = (s + 2) / (s ** 2 + 6 * s + 25)

w, mag, phase = sys2.bode() # Diagrama de bode: frecuencias, magnitud y fase
fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(6, 6))
plt.grid(True)

ax1.semilogx(w, mag) # Eje x logarítmico
ax1.set_title('Diagrama de Bode')
ax2.semilogx(w, phase) # Eje x logarítmico

w, H = signal.freqresp(sys2)
fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(8, 4))
plt.grid(True)
ax1.plot(H.real, H.imag)
ax1.plot(H.real, -H.imag)
ax2.plot(sys2.zeros.real, sys2.zeros.imag, 'o')
ax2.plot(sys2.poles.real, sys2.poles.imag, 'x')


plt.show()
