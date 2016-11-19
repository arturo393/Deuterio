# -*- coding: latin-1 -*-

import math
import numpy as np 
import matplotlib.pyplot as plt

import numpy as np


"""
En el siguiente programa, se obtienen busca obtener los parámetros de un sistema de segundo orden para las celdas de electrólsis
--> Amortiguamiento
-->
-->
-->
-->
-->
"""
from scipy import signal

## Parametros de entrada
u = 12; # Escalon [V]

## Parametros de la respuesta a escalon
td = 0; # Tiempo de retardo, td
tr = 0; # Tiempo de levantamiento, tr 
tp = 0; # Tiempo pico, tp 
Mp = 0; # Sobrepaso máximo, Mp
ts = 0; # Tiempo de asentamiento, ts 
y = 20; # Voltaje máximo de respuesta en [V]

## Parámetros de la función de transferencia
K = y/u;   # Ganancia del sistema
wn = 2; # frecuencua natural
psi = 0.5; # coeficiente de amortiguamiento relativo 

sys2 = signal.lti(K*wn**2, [1, 2*psi*wn, wn**2]) # H(s) = (s + 2) / (s ** 2 + 6 * s + 25)
w, H = signal.freqresp(sys2)
fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(8, 4))
ax1.plot(H.real, H.imag)
ax1.plot(H.real, -H.imag)
ax2.plot(sys2.zeros.real, sys2.zeros.imag, 'o')
ax2.plot(sys2.poles.real, sys2.poles.imag, 'x')



