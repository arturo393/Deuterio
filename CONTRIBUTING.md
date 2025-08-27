# Guía para Contribuir al Proyecto Deuterio

¡Gracias por tu interés en contribuir al proyecto Deuterio! Esta guía te ayudará a entender cómo participar efectivamente en el desarrollo.

## Código de Conducta

### Principios Fundamentales
- Mantener un ambiente respetuoso y profesional
- Enfocarse en el avance científico y técnico
- Respetar diferentes perspectivas y enfoques
- Seguir prácticas de investigación responsable

## Tipos de Contribuciones Bienvenidas

### 1. Mejoras en el Código
- Optimización de algoritmos matemáticos
- Corrección de bugs en scripts de Python
- Mejoras en código de Arduino/microcontroladores
- Refactorización para mejor legibilidad

### 2. Documentación
- Correcciones en documentación técnica
- Traducción de contenido (español/inglés)
- Mejoras en comentarios del código
- Actualización de diagramas y figuras

### 3. Validación Experimental
- Replicación de experimentos
- Reportes de resultados experimentales
- Análisis de datos adicionales
- Validación de modelos matemáticos

### 4. Investigación Adicional
- Referencias científicas relevantes
- Análisis comparativo con otros métodos
- Propuestas de mejoras teóricas
- Estudios de viabilidad

## Flujo de Trabajo Git

### Configuración Inicial
```bash
# Configurar información personal
git config --global user.name "Tu Nombre"
git config --global user.email "tu.email@ejemplo.com"

# Clonar el repositorio
git clone https://github.com/arturo393/Deuterio.git
cd Deuterio

# Configurar repositorio upstream (si es fork)
git remote add upstream https://github.com/arturo393/Deuterio.git
```

### Proceso de Desarrollo

#### 1. Crear una Nueva Rama
```bash
# Actualizar rama principal
git checkout master
git pull upstream master

# Crear rama para nueva característica
git checkout -b feature/nombre-descriptivo
# Ejemplos:
# git checkout -b feature/optimizar-modelo-segundo-orden
# git checkout -b fix/corregir-calculo-capacitancia
# git checkout -b docs/actualizar-readme
```

#### 2. Convenciones de Nombres de Ramas
- `feature/descripcion` - Nuevas características
- `fix/descripcion` - Corrección de errores
- `docs/descripcion` - Cambios en documentación
- `refactor/descripcion` - Refactorización de código
- `experiment/descripcion` - Trabajo experimental

#### 3. Realizar Cambios
```bash
# Hacer cambios en los archivos
# Probar los cambios localmente

# Agregar archivos modificados
git add archivo1.py archivo2.tex

# Confirmar cambios con mensaje descriptivo
git commit -m "Descripción clara de los cambios"
```

#### 4. Convenciones de Commits

##### Formato de Mensajes
```
tipo(alcance): descripción breve

Descripción detallada opcional explicando:
- Qué cambios se hicieron
- Por qué se hicieron
- Cómo afectan al proyecto

Fixes #numero-de-issue (si aplica)
```

##### Tipos de Commits
- `feat`: Nueva característica
- `fix`: Corrección de error
- `docs`: Cambios en documentación
- `style`: Cambios de formato (espacios, indentación)
- `refactor`: Refactorización sin cambios funcionales
- `test`: Agregar o modificar pruebas
- `chore`: Tareas de mantenimiento

##### Ejemplos
```bash
git commit -m "feat(modelamiento): agregar análisis de resonancia LC"

git commit -m "fix(sensores): corregir lectura de temperatura MAX6675"

git commit -m "docs(readme): actualizar instrucciones de instalación"
```

### 5. Enviar Pull Request

#### Antes de Enviar
```bash
# Actualizar rama con últimos cambios
git fetch upstream
git rebase upstream/master

# Ejecutar pruebas (si existen)
python -m pytest tests/

# Verificar que el código Python funciona
python Codigos/Modelamiento/sistema_de_segundoorden.py
```

#### Crear Pull Request
1. Subir rama al repositorio
```bash
git push origin feature/nombre-descriptivo
```

2. Crear Pull Request en GitHub con:
   - Título descriptivo
   - Descripción detallada de cambios
   - Referencias a issues relacionados
   - Checklist de verificación

## Estándares de Código

### Python
- Seguir PEP 8 para estilo de código
- Usar nombres de variables descriptivos en español o inglés consistente
- Comentar algoritmos complejos
- Incluir docstrings para funciones importantes

```python
def calcular_capacitancia_tubos(radio_interior, radio_exterior, altura, permitividad):
    """
    Calcula la capacitancia entre tubos concéntricos.
    
    Args:
        radio_interior (float): Radio del tubo interior en metros
        radio_exterior (float): Radio del tubo exterior en metros
        altura (float): Altura de los tubos en metros
        permitividad (float): Permitividad del medio
    
    Returns:
        float: Capacitancia en Faradios
    """
    import math
    return permitividad * 2 * math.pi * altura / math.log(radio_exterior / radio_interior)
```

### Arduino/C
- Usar indentación consistente (2 espacios)
- Comentar configuraciones importantes
- Usar nombres descriptivos para pines y constantes

```c
// Configuración de pines para sensor de temperatura
const int TEMP_SENSOR_CS = 10;   // Chip Select
const int TEMP_SENSOR_SCK = 13;  // Serial Clock
const int TEMP_SENSOR_SO = 12;   // Serial Output

// Inicializar sensor de temperatura
void inicializar_sensor_temperatura() {
    pinMode(TEMP_SENSOR_CS, OUTPUT);
    digitalWrite(TEMP_SENSOR_CS, HIGH);
}
```

### LaTeX
- Mantener estructura consistente de documentos
- Usar referencias apropiadas para ecuaciones y figuras
- Incluir comentarios para secciones complejas

## Proceso de Revisión

### Checklist para Pull Requests
- [ ] El código ejecuta sin errores
- [ ] Se siguieron las convenciones de estilo
- [ ] Se agregó documentación necesaria
- [ ] Se actualizaron archivos relevantes (README, etc.)
- [ ] Los cambios son coherentes con el objetivo del proyecto
- [ ] Se incluyeron pruebas si es apropiado

### Criterios de Aceptación
1. **Calidad Técnica**: El código es funcional y eficiente
2. **Documentación**: Los cambios están bien documentados
3. **Coherencia**: Compatible con la arquitectura existente
4. **Investigación**: Basado en fundamentos científicos sólidos

## Reportar Issues

### Tipos de Issues
- **Bug**: Error en el código existente
- **Enhancement**: Mejora o nueva característica
- **Question**: Pregunta sobre el proyecto
- **Research**: Propuesta de investigación adicional

### Formato para Reportar Bugs
```markdown
## Descripción del Error
Descripción clara del problema encontrado.

## Pasos para Reproducir
1. Ejecutar script `script_name.py`
2. Usar parámetros específicos
3. Observar error en línea X

## Comportamiento Esperado
Descripción de lo que debería suceder.

## Entorno
- Sistema Operativo: 
- Versión de Python:
- Librerías instaladas:

## Información Adicional
Cualquier contexto adicional sobre el problema.
```

## Recursos Adicionales

### Documentación de Referencia
- [Documentación de NumPy](https://numpy.org/doc/)
- [Documentación de SciPy](https://docs.scipy.org/)
- [Documentación de Arduino](https://www.arduino.cc/reference/)

### Investigación Científica
- Artículos sobre electrólisis del agua
- Referencias sobre sistemas de segundo orden
- Estudios de eficiencia energética

## Contacto

Para preguntas específicas sobre contribuciones:
- Abrir un issue en GitHub
- Contactar al mantenedor: a.veras@gmail.com

---

**Nota**: Este proyecto es de naturaleza investigativa. Todas las contribuciones deben mantener rigor científico y transparencia en metodologías y resultados.