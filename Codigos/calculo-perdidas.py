# -*- coding: latin-1 -*-

import numpy as np
import matplotlib.pyplot as plt

"""Calculo de perdidas en mosfet, y relaciones con Vth."""

Vgs=10; #Vgs aplicado
Rds=0.27; #Rds cuando mosfet esta activo [ohm]
D=0.5; #ciclo de trabajo 
Vin=50; #Voltage alimentación
Iout=20; #Corriente salida
Fsw=100E3; #Frecuencia switching
tr=58E-9;# tiempo de subida mosfet [ns]
tf=59E-9; #tiempo de bajada mosfet [ns]

Pc=np.power(Iout,2)*Rds*D ; #Disipación de energía por Isalida
Psw=0.5*Vin*Iout*(tr+tf)*Fsw; #Disipación de energía por switching



print(f"Potencia Continua: {Pc:.3f} [W]")
print(f"Potencia Switching: {Psw:.3f} [W]")
print(f"Potencia Total: {Pc+Psw:.3f} [W]") 
