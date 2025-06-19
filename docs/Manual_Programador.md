# Manual del Programador - Cut the Capibara

## Índice
1. [Introducción](#introducción)
2. [Requisitos del Sistema](#requisitos-del-sistema)
3. [Estructura del Proyecto](#estructura-del-proyecto)
4. [Arquitectura del Software](#arquitectura-del-software)
5. [Clases Principales](#clases-principales)
6. [Sistema de Controles](#sistema-de-controles)
7. [Sistema de Animación](#sistema-de-animación)
8. [Sistema de Física](#sistema-de-física)
9. [Sistema de Audio](#sistema-de-audio)
10. [Compilación y Ejecución](#compilación-y-ejecución)
11. [Depuración](#depuración)
12. [Extensión del Juego](#extensión-del-juego)

## Introducción

Cut the Capibara es un juego inspirado en el clásico "Cut the Rope", desarrollado utilizando C++ y la biblioteca SFML. El objetivo del juego es cortar cuerdas estratégicamente para guiar un dulce hacia un personaje, evitando obstáculos y recogiendo estrellas en el proceso.

Este manual está dirigido a programadores que deseen entender la estructura interna del juego, modificar su comportamiento o extenderlo con nuevas funcionalidades.

## Requisitos del Sistema

### Requisitos de Desarrollo
- Sistema Operativo: Windows 10 o superior
- MinGW-w64 con GCC 11.0 o superior
- SFML 2.5.1 o superior instalado en C:/msys64/mingw64/
- 2 GB de RAM mínimo recomendado
- Editor de código (VS Code recomendado)

### Herramientas Recomendadas
- Visual Studio Code con las extensiones:
  - C/C++
  - CMake
  - C/C++ Extension Pack

## Estructura del Proyecto

El proyecto sigue una estructura organizada por carpetas para facilitar su mantenimiento:

```
Proyecto3P/
│
├── assets/              # Recursos del juego
│   ├── fonts/           # Archivos de fuentes tipográficas
│   ├── images/          # Imágenes y sprites
│   └── sound/           # Archivos de música y efectos de sonido
│
├── bin/                 # Archivos binarios y ejecutable
│
├── docs/                # Documentación del proyecto
│
├── include/             # Archivos de cabecera (.hpp)
│
├── src/                 # Archivos de código fuente (.cpp)
│
└── Makefile             # Script de compilación
```

## Arquitectura del Software

El juego utiliza una arquitectura basada en componentes donde cada objeto del juego es una clase independiente que puede ser creada, configurada y destruida según las necesidades. La comunicación entre componentes se realiza mediante referencias y punteros.

El ciclo de vida del juego sigue el siguiente flujo:
1. Inicialización: Carga de recursos, configuración inicial
2. Bucle principal: Actualización de estado, manejo de eventos, renderizado
3. Finalización: Liberación de recursos

## Clases Principales

### Clase `Menu`
Gestiona el menú principal del juego, permitiendo al jugador iniciar un nivel, acceder a las opciones o salir.

**Métodos clave:**
- `Menu(sf::RenderWindow& win)`: Constructor que inicializa el menú.
- `OpcionMenu Mostrar()`: Muestra el menú y devuelve la opción seleccionada.

### Clase `Tutorial`
Implementa el nivel tutorial del juego, encargándose de la lógica, la física y la renderización de este nivel.

**Métodos clave:**
- `Tutorial(sf::RenderWindow& win)`: Constructor que inicializa el nivel.
- `void Ejecutar()`: Ejecuta el bucle principal de juego para este nivel.

### Clase `Rope`
Representa una cuerda física en el juego, utilizando un sistema de simulación de física basado en el algoritmo de Verlet.

**Métodos clave:**
- `Rope(const sf::Vector2f& start, const sf::Vector2f& end, int segments = 20)`: Constructor para crear una cuerda entre dos puntos.
- `void update(float dt)`: Actualiza la física de la cuerda.
- `void draw(sf::RenderWindow& window)`: Renderiza la cuerda en pantalla.
- `void cutAtSegment(size_t segmentIdx)`: Corta la cuerda en un punto específico.

### Clase `Cake`
Representa el dulce que el jugador debe guiar hacia el personaje.

**Métodos clave:**
- `Cake(const sf::Vector2f& pos)`: Constructor que posiciona el dulce.
- `void update(float dt)`: Actualiza la animación y el estado del dulce.
- `sf::Vector2f getPosition()`: Obtiene la posición actual del dulce.

### Clase `MenuControles`
Gestiona los controles del juego, permitiendo interacciones mediante teclado, ratón y gamepad.

**Métodos clave:**
- `static void actualizar(Event& event)`: Actualiza el estado de los controles.
- `static bool estaPresionada(Keyboard::Key tecla)`: Verifica si una tecla está presionada.

### Clase `PantallaVictoria`
Muestra la pantalla de victoria cuando el jugador completa un nivel con éxito.

**Métodos clave:**
- `PantallaVictoria(sf::RenderWindow& win)`: Constructor para inicializar la pantalla.
- `void Mostrar()`: Muestra la pantalla de victoria con animaciones.

## Sistema de Controles

El sistema de controles está implementado en la clase `MenuControles`, que utiliza un array estático para mantener el estado de cada tecla. Esta estrategia permite:

1. Verificar el estado de las teclas desde cualquier parte del código.
2. Soportar múltiples teclas presionadas simultáneamente.
3. Facilitar la detección de combinaciones de teclas.

**Ejemplo de uso:**
```cpp
if (MenuControles::estaPresionada(sf::Keyboard::Space)) {
    // Realizar acción al presionar espacio
}

sf::Vector2f posicionRaton = MenuControles::mousePosicion(ventana);
```

## Sistema de Animación

Las animaciones en el juego utilizan dos métodos principales:

1. **Animación por frames**: Utilizada para personajes y elementos como el dulce. Se implementa mediante arrays de texturas que se alternan según un temporizador.

2. **Animación procedural**: Utilizada para elementos como la cuerda y efectos visuales. Se implementa mediante cálculos en tiempo real basados en parámetros físicos.

**Ejemplo de implementación de animación por frames:**
```cpp
animTimer += deltaTime;
if (animTimer >= animSpeed) {
    currentFrame = (currentFrame + 1) % animFrames.size();
    sprite.setTexture(animFrames[currentFrame]);
    animTimer = 0.f;
}
```

## Sistema de Física

La física del juego se basa en dos componentes principales:

1. **Física de cuerda**: Implementada mediante el algoritmo de Verlet, que simula puntos conectados por restricciones de distancia. Este algoritmo proporciona una simulación estable y eficiente de la cuerda.

2. **Colisiones**: Implementadas mediante detección de intersecciones entre formas geométricas (círculos, rectángulos).

La actualización física sigue estos pasos:
1. Actualizar posiciones basadas en velocidades (integración de Verlet).
2. Aplicar restricciones de distancia entre puntos conectados.
3. Resolver colisiones con objetos estáticos.
4. Actualizar visual según las nuevas posiciones.

## Sistema de Audio

El audio del juego está gestionado por dos clases:

1. **Clase `Music`**: Gestiona la reproducción de música de fondo con funcionalidades para cargar, reproducir, pausar y detener archivos de audio.

2. **Clase `MusicButton`**: Proporciona una interfaz gráfica para controlar la reproducción de música.

**Ejemplo de uso:**
```cpp
Music music;
music.load("assets/sound/background.ogg");
music.play();
```

## Compilación y Ejecución

### Compilación
El proyecto utiliza un Makefile para simplificar el proceso de compilación. Los comandos principales son:

```bash
# Compilar el proyecto
mingw32-make

# Compilar y ejecutar
mingw32-make run

# Limpiar archivos compilados
mingw32-make clean
```

### Dependencias
Las dependencias externas que deben estar instaladas son:
- SFML 2.5.1 o superior (Graphics, Window, System, Audio)
- MinGW con soporte para C++17

### Comandos de Compilación Manual
Si se desea compilar manualmente sin usar el Makefile:

```bash
g++ -std=c++17 -Iinclude -IC:/msys64/mingw64/include -g src/*.cpp -o bin/game.exe -LC:/msys64/mingw64/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
```

## Depuración

Para la depuración del juego, se recomienda:

1. Utilizar la opción `-g` del compilador (ya incluida en el Makefile).
2. Configurar un depurador como GDB en Visual Studio Code.
3. Utilizar los mensajes de consola incluidos en el código con `std::cerr` para problemas de carga de recursos.

**Ejemplo de configuración de depuración en VS Code (launch.json):**
```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Debug Cut the Capibara",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/bin/game.exe",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "externalConsole": true,
            "MIMode": "gdb",
            "miDebuggerPath": "C:/msys64/mingw64/bin/gdb.exe",
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ],
            "preLaunchTask": "build"
        }
    ]
}
```

## Extensión del Juego

### Añadir Nuevos Niveles
Para añadir un nuevo nivel al juego:

1. Crear una nueva clase derivada del patrón de `Tutorial`.
2. Implementar la lógica específica del nivel.
3. Añadir una opción para acceder al nivel desde el menú principal.

### Añadir Nuevos Elementos
Para añadir nuevos elementos jugables:

1. Crear una nueva clase para el elemento.
2. Implementar métodos de actualización y renderizado.
3. Integrar el elemento en las clases de nivel correspondientes.

### Modificar la Física
Para ajustar el comportamiento físico:

1. Modificar los parámetros de gravedad en la clase `Rope`.
2. Ajustar las constantes de elasticidad y fricción según sea necesario.
3. Modificar los algoritmos de detección de colisiones para nuevos comportamientos.

---

Desarrollado por [Inei-Zone] - 2025
