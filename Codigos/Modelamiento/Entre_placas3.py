# -*- coding: latin-1 -*-

import math
import numpy as np 
import matplotlib.pyplot as plt
import matplotlib.pyplot as plt
import numpy as np

"""
En el siguiente programa, se obtienen los valores de los efectos producidos entre tubos concentricos debidos a la excitacón 
electromagnetica proveniente de una fuente de Voltaje.
Los efectos a analizar son:
-> Voltage entre placas
-> Campo electrico entre placas 
-> Cargas existentes entre placas
-> Fuerzas de lorentz sobre las moleculas
-> Circuito RLC y Resonacia.
"""

################definiciones###############
#caracteristicas celdas
"""Se tienen 2 celdas concentricas de radios:
r1=5,5 mm
r2=11 mm
""" 
d1=0.011 ;       # diametro tubo interior en [m]
r1=d1/2;         # radio tubo interior
d2=0.022 ;       # dimetro tubo exterior en [m]
r2=d2/2;         # radio tubo exterior
cascara=0.00158; # ?? [m]
h1= 0.15         # altura de los tubos [m]
#h1 = 1; # [m]

Area_2=math.pi*(r2)**2;         # Area tubo d1 grande en [m]²
Area_1=math.pi*(r1+cascara)**2; # Area tubo d2 + cascara [m]²
Diferencia_Area= Area_2-Area_1; # Area entre ambos electrodos[m]²


Vol=Diferencia_Area*h1; #Volumen entre placas [m]³
Litros=Vol*1000;        #Volumen en litros
Litros2=Vol*1e6;      
d=r2-r1;                # distancia entre placas

#######Coversión de Unidades######
PM_agua = 18; ## peso molecular del agua [gr/mol]
moles = Litros*1000/18;      # Moles de agua en volumen de liquido [mol]
moleculas = 6.02*1e23*moles; # Numero de moleculas en un mol [molec]

#Moles_OH=;
#Moles_H2+=;

###Cargas Moleculares######
H= 0.335;        #carga Hidrogeno en molecula de agua [C]
O=-0.671;        #carga Oxigeno en molecula de agua  [C]
q=1.6*1e-19;     #Carga electron [C]
F = 96485.33289; # constante de faraday [C/mol]


#####Caracteristicas Electricas#####
Per_0 = 8.85*1e-12;   # Permitividad del vacio [F/m]
Per_r = 80;           # Permitividad relativa del agua
Per = Per_0*Per_r;    # Permitividad absoluta
u_o = 4*math.pi*1e-7; # Permeabilidad del vacio
u_r =  1500;          # Permeabilidad relativa del ?
u_total = u_o*u_r;    # Permeabilidad absoluta

#####Capacitancia Placas paraleas######
## MODIFICABLE ##
alto_p = 0.2;    # alto de la placa en [m]
ancho_p = 0.1;   # ancho de la placa en [m]
distancia_p = 0.03; # distancia entre placas [m]

## Ecuaciones - NO MODIFICAR ##
Vol = distancia_p*alto_p*ancho_p;
Litros=Vol*1000;                      # Volumen [L]
PM_agua = 18;                         # peso molecular del agua [gr/mol]
densidad_agua = 1000;                 # Densidad del agua [gr/L]
moles = Litros*densidad_agua/PM_agua; # Moles de agua en volumen de liquido [mol]
moleculas = 6.02*1e23*moles;          # Numero de moleculas en un mol [molec]
App = alto_p*ancho_p;                 # Area superficial de la placa en [m2]
C = Per*App/distancia_p;              # Capacitancia de celda con electrolito de agua
C_total = C;

#####Capacitancia tubos######
#n_tubos = 1;
#C=Per*2*math.pi*h1/np.log(r2/r1);  #Capacitancia de celda con electrolito de agua
#C_total=n_tubos*C;

V = 1.23;                     # Voltaje entre placas/tubos [V]
Q_tot = C*V;                  # Carga total entre tubos [C]
E_tubo = Q_tot / (d*C);       # Campo electrico total entre tubos [V/m]
U_tubo = Q_tot*Q_tot/(2*C);   # Energía entre tubos [J]
G = 2*F*V;                    # Energía libre de Gibbs [J/mol]
G_vol = G*moles;              # Energía libre Gibss en el volumen de placas/tubos [J]
Vmin = math.sqrt(2*G_vol/C_total); # Voltaje mínimo en capacitor para energía entre tubos/placas [V]

print "Voltaje entre tubos=",V,"[V]";
print "Carga entre tubos=",Q_tot,"[C]";
print "Campo electrico=",E_tubo,"[V/m]";
print "Energia entre tubos=",U_tubo/moles,"[J/mol]";
print "Energía libre de Gibss = ",G/1000,"[kJ/mol]"
print "Energía libre de Gibss entre placas = ",G*moles/1000,"[kJ]"
print "Voltaje minimo para separ el agua entre tubos = ",Vmin/1000000,"[MV]"

Rc = 0.001; # Resistencia del capacitor en [ohm]

#er= np.arange(1, 80, 1);
#Cplot=Per_0*er*App/distancia_p;
#plt.plot(er,Cplot);
#plt.show();
###########################################

#####Inductancia y Resistencia######
N = 130; #vueltas
A_tor = 0.50*0.43; # [m]
r_tor = 0.9/2 + 0.43/2; #[m]
L_total = u_total*(N)**2*A_tor/(2*math.pi*r_tor);
Rl = 0.001; # resitencia del inductor en [ohm]

### Excitacion circuito RLC ###
f_act = 100;                         # frecuencia de actuación en [hz]
Xl = 2*math.pi*f_act*L_total + Rl;   # impedancia inductor
Xc = 1/2*math.pi*f_act*C_total + Rc;     # impedancia capacitor

Z = Xc - Xl;                         # impedancia total

f_res = 1 / (2*math.pi*math.sqrt(C_total*L_total));

###############Cargas#####################
"""El agua se separa en OH- y H2+ """

#Carga de un mol de inoes monovalentes = 96488[C]
cte_F=96488; [C]
carga_mol_OH=96488*moles; #carga un mol OH-

###tiempo

t=np.arange(0,10,1); #tiempo [s]


###########################Sucesos###############################################

print "----------------Cantidades volumentricas----------------------";

print "Volumen de agua entre placas",Vol,"[m]³",Litros2,"[cm³]",Litros,"[L]";

print "moles de agua en reactor=",moles, "[moles]";

print "numero de moleculas",moleculas,"[moleculas]";

######Energia en puentes de Hidrogeno en el Volumen, habiendo 4 puentes por molecula, energia de puente/mol= 40[KJ/mol]

Energia_en_puentes=237*moles;

print"Energia en puentes de Hidrogeno",Energia_en_puentes,"[KJ]";

print"--------------Cantidades electricas----------------";

print "Capacitancia =",C_total,"[F]"
print "Inductancia =",L_total,"[H]"
print "Frecuencia de resonancia =", f_res,"[Hz]"



print "-------------Cantidades moleculares y ionias--------------";


print "carga mol OH- =",carga_mol_OH,"[C]"





###############Fuerza Lorentz##############
"""F=q*(E) #Fuerza de lorentz no tomando en cuenta velocidad de carga ni campo magnetico
print "Fuerza de lorentz instantanea=",F,"[N]";
"""
###########################################

