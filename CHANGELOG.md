# Changelog

Todos los cambios notables en el proyecto Deuterio serán documentados en este archivo.

El formato está basado en [Keep a Changelog](https://keepachangelog.com/es-ES/1.0.0/),
y este proyecto adhiere al [Versionado Semántico](https://semver.org/lang/es/).

## [No Versionado] - 2016-12-22

### Agregado
- Documentación inicial del proyecto
- Scripts de modelamiento matemático para sistemas de electrólisis
- Código de control para microcontroladores Arduino
- Documentación técnica en LaTeX sobre prototipos EPS

### Último Update - 2016-12-22
- **Commit**: `d80fab8` - Update general del repositorio
- Actualizaciones finales en documentación y código

### Imágenes y Recursos - 2016-12-22
- **Commit**: `ee187b8` - Imagenes de deuterio renovadas
- Actualización de recursos gráficos del proyecto
- Mejoras en material visual para documentación

### Modelamiento Avanzado - 2016-11-21
- **Commit**: `4f72b5e` - Se agregar parte de modelamiento
- Implementación de nuevos modelos matemáticos
- Expansión de capacidades de análisis

### Sistemas de Segundo Orden - 2016-11-21
- **Commit**: `d1bac62` - Se agrega parámetros de identificación del sistema más las ecuaciones
- Implementación completa de análisis de sistemas de segundo orden
- Ecuaciones para identificación de parámetros de celdas de electrólisis
- Cálculos de respuesta transitoria

### Fundamentos Matemáticos - 2016-11-19
- **Commit**: `55c5a19` - Se comienza código para determinar parámetros de un sistema de segundo orden de la celda de electrólisis
- Inicio del modelamiento matemático de celdas como sistemas de segundo orden
- Fundamentos teóricos para análisis de respuesta dinámica

- **Commit**: `ee451cd` - Se comienza la parte del sistema de segundo orden
- Estructura inicial para análisis de sistemas dinámicos

### Mejoras en Control de Frecuencia - 2016-11-10
- **Commit**: `54a376b` - Se agrego la opción de cambiar el preescaler
- Funcionalidad para modificar prescaler en generación de señales
- Mayor flexibilidad en control de frecuencias

### Cálculos de Frecuencia - 2016-11-09
- **Commit**: `6112c68` - Se agrega cálculo de frecuencia. Falta probar
- Implementación de cálculos de frecuencia para señales de control
- Algoritmos para determinación de parámetros de temporización

- **Commit**: `99b3f3f` - Arreglo de errores
- Correcciones en código existente
- Resolución de bugs en implementación

## Componentes Principales Desarrollados

### Modelamiento Matemático
- **Sistema de segundo orden** (`sistema_de_segundoorden.py`)
  - Análisis de respuesta transitoria de celdas de electrólisis
  - Cálculo de parámetros de amortiguamiento y frecuencia natural
  - Generación de diagramas de Bode

- **Análisis entre placas** (`Entre_placas3.py`)
  - Cálculos de campos eléctricos entre electrodos concéntricos
  - Determinación de capacitancias e inductancias
  - Análisis de resonancia en circuitos LC

- **Cálculo de pérdidas** (`calculo-perdidas.py`)
  - Análisis de pérdidas en MOSFETs
  - Cálculos de disipación por conmutación
  - Optimización de eficiencia energética

### Control Electrónico
- **Sensores** (`Codigos/Sensores/`)
  - Interfaz con sensores de temperatura MAX6675
  - Sistemas de adquisición de datos
  - Código para microcontroladores Arduino

- **Generación de Pulsos** (`Codigos/Pulsos/`)
  - Control de temporización con timers
  - Generación de señales de control
  - Configuración de prescalers

### Documentación Técnica
- **Big Bobbin** (`Informes/Big Bobbin/`)
  - Fundamentos teóricos de electrólisis no convencional
  - Referencias a investigaciones de Puharich y Meyer
  - Metodologías experimentales

- **Prototipos EPS** (`Informes/EPS-CORFO-PROTOTIPO/`)
  - Especificaciones de sistemas de potencia electrónica
  - Requerimientos funcionales y técnicos
  - Diseño de racks y gabinetes

## Tecnologías y Herramientas

### Software
- **Python**: NumPy, SciPy, Matplotlib para modelamiento
- **Arduino IDE**: Desarrollo de código para microcontroladores
- **LaTeX**: Documentación técnica y científica

### Hardware
- **Microcontroladores**: Arduino para control y adquisición
- **Sensores**: MAX6675 para medición de temperatura
- **Electrónica de potencia**: MOSFETs y circuitos de conmutación

## Notas de Desarrollo

### Estado del Proyecto
- Proyecto experimental de investigación
- Desarrollo activo entre 2016
- Enfoque en validación teórica y prototipado

### Metodología
- Desarrollo incremental de modelos matemáticos
- Validación experimental en paralelo
- Documentación científica rigurosa

### Colaboradores
- **Desarrollador Principal**: arturo393 (a.veras@gmail.com)
- Proyecto individual de investigación

---

**Nota**: Este changelog fue construido retrospectivamente basado en el historial de commits del repositorio. Las fechas y descripciones reflejan el desarrollo histórico del proyecto.