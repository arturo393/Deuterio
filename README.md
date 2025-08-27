# Deuterio

## Descripción del Proyecto

Deuterio es un proyecto de investigación centrado en métodos no convencionales de electrólisis del agua para la generación de hidrógeno. El proyecto combina modelamiento matemático, sistemas de control electrónico y prototipos experimentales para explorar técnicas avanzadas de separación del agua inspiradas en investigaciones pioneras de científicos como Andrija Puharich y Stanley Meyer.

## Arquitectura del Proyecto

### Estructura de Directorios

```
Deuterio/
├── Codigos/              # Scripts de modelamiento y control
│   ├── Modelamiento/     # Modelos matemáticos en Python
│   ├── Sensores/         # Código de Arduino para sensores
│   ├── Pulsos/           # Generación de pulsos para control
│   └── Convertidor/      # Sistemas de conversión de potencia
├── Informes/             # Documentación técnica en LaTeX
│   ├── Big Bobbin/       # Documentos de diseño del sistema
│   ├── EPS-CORFO-PROTOTIPO/ # Reportes del prototipo EPS
│   └── ...
├── Imagen/               # Recursos gráficos
└── ideas_negocio_desarrollo/ # Materiales de desarrollo comercial
```

### Componentes Principales

1. **Modelamiento Matemático** (`Codigos/Modelamiento/`)
   - Análisis de sistemas de segundo orden para celdas de electrólisis
   - Cálculos de campos eléctricos entre placas concéntricas
   - Análisis de pérdidas en componentes electrónicos

2. **Control Electrónico** (`Codigos/Sensores/`, `Codigos/Pulsos/`)
   - Sistemas de adquisición de datos con sensores
   - Generación de señales de control
   - Interfaz con microcontroladores Arduino

3. **Documentación Técnica** (`Informes/`)
   - Fundamentación teórica de métodos de electrólisis
   - Especificaciones de prototipos EPS (Electronic Power System)
   - Análisis experimental y resultados

## Requisitos del Sistema

### Dependencias de Python
```bash
numpy
matplotlib
scipy
```

### Hardware
- Microcontroladores Arduino (para código de sensores)
- Componentes electrónicos específicos mencionados en documentación

### Software Adicional
- LaTeX (para compilar documentación técnica)
- Compilador de Arduino IDE

## Instalación

### 1. Clonar el Repositorio
```bash
git clone https://github.com/arturo393/Deuterio.git
cd Deuterio
```

### 2. Instalar Dependencias de Python
```bash
pip install numpy matplotlib scipy
```

### 3. Configurar Entorno Arduino
- Instalar Arduino IDE
- Configurar librerías específicas mencionadas en el código

## Uso

### Ejecutar Modelos Matemáticos

#### Sistema de Segundo Orden
```bash
cd Codigos/Modelamiento
python sistema_de_segundoorden.py
```
Este script analiza la respuesta transitoria de celdas de electrólisis modeladas como sistemas de segundo orden.

#### Análisis de Campos Eléctricos
```bash
python Entre_placas3.py
```
Calcula campos eléctricos, capacitancias e inductancias en configuraciones de placas concéntricas.

#### Cálculo de Pérdidas
```bash
python calculo-perdidas.py
```
Analiza pérdidas de potencia en MOSFETs y componentes de switching.

### Programar Microcontroladores
1. Abrir Arduino IDE
2. Cargar archivos `.ino` desde `Codigos/Sensores/` o `Codigos/Pulsos/`
3. Configurar placa y puerto apropiados
4. Compilar y subir código

### Compilar Documentación
```bash
cd Informes/Big\ Bobbin/
pdflatex BB.tex
```

## Características Técnicas

### Métodos de Electrólisis Estudiados
- Electrólisis convencional
- Métodos de ionización por colisión
- Técnicas de resonancia LC
- Generación de pulsos de alta frecuencia

### Parámetros de Diseño
- Voltajes de operación: 1.23V - 50V
- Frecuencias de switching: 100 kHz típico
- Configuraciones de placas concéntricas
- Análisis de sistemas de segundo orden

## Estado del Proyecto

Este proyecto representa investigación experimental en métodos alternativos de electrólisis. Los resultados son de naturaleza exploratoria y requieren validación experimental adicional.

### Componentes Completados
- ✅ Modelamiento matemático básico
- ✅ Prototipos de sistemas EPS
- ✅ Código de control para microcontroladores
- ✅ Documentación técnica fundamental

### Trabajo Futuro
- Validación experimental completa
- Optimización de eficiencia energética
- Escalamiento de prototipos
- Análisis de viabilidad comercial

## Contribuciones

Este proyecto fue desarrollado como parte de investigación científica. Para información sobre contribuciones, consulte el archivo CONTRIBUTING.md.

## Licencia

Ver archivo LICENSE para detalles de licencia.

## Contacto

Proyecto desarrollado por: arturo393
Email: a.veras@gmail.com

## Referencias Científicas

El proyecto se basa en investigaciones previas de:
- Andrija Puharich - Métodos de separación molecular del agua
- Stanley Meyer - Tecnologías de celdas de agua
- Investigación en electrólisis no convencional y generación de gas de Brown

---

**Nota**: Este proyecto es de naturaleza experimental e investigativa. Los métodos y resultados presentados requieren validación científica rigurosa antes de cualquier aplicación práctica.