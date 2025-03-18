# Proyecto: Sistema de Apoyo para el Juego Risk

## Descripción
Este proyecto consiste en la implementación de un sistema basado en consola para la gestión del juego *Risk*. El sistema permite la inicialización del juego, el manejo de turnos, la simulación de ataques, la fortificación de territorios y el almacenamiento de partidas utilizando la codificación de Huffman. Además, ofrece herramientas para apoyar la toma de decisiones estratégicas en el juego.

## Características
- Configuración del juego con asignación de territorios y turnos.
- Gestión de ataques y movimientos estratégicos.
- Almacenamiento y carga de partidas con compresión de datos.
- Asistencia en la toma de decisiones para optimizar jugadas.

## Requisitos
- **Compilador:** gnu-g++ v4.0.0 o superior
- **Lenguaje:** C++

## Estructura del Proyecto
```
📂 Risk-Game-Assistant
├── 📁 src                # Código fuente
├── 📁 data               # Archivos de juegos guardados
├── 📁 docs               # Documentación del proyecto
└── 📄 README.md          # Documentación general
```

## Comandos Implementados
### 🕹️ Configuración del Juego
- **`inicializar`**: Inicia el juego, asigna territorios y establece los turnos.
- **`turno <id_jugador>`**: Realiza las operaciones de un turno (reclutar, atacar, fortificar).
- **`salir`**: Finaliza la ejecución del sistema.

### 💾 Almacenamiento de Partidas
- **`guardar <nombre_archivo>`**: Guarda el estado actual en un archivo de texto.
- **`guardar_comprimido <nombre_archivo>`**: Guarda el estado en un archivo comprimido (.bin) usando codificación de Huffman.
- **`inicializar <nombre_archivo>`**: Carga una partida desde un archivo de texto o binario.

### 🧠 Estrategias de Juego
- **`costo_conquista <territorio>`**: Calcula el costo y la secuencia de territorios necesarios para conquistar el territorio objetivo.
- **`conquista_mas_barata`**: Sugiere la conquista más barata posible considerando las unidades de ejército.

### ❓ Ayuda
- **`ayuda`**: Muestra una lista de los comandos disponibles.
- **`ayuda <comando>`**: Muestra la ayuda específica de un comando.

## Ejecución
1. Clona el repositorio:
```bash
git clone https://github.com/tu_usuario/risk-game.git
```
2. Compila el proyecto:
```bash
g++ -o risk-game src/*.cpp
```
3. Ejecuta la aplicación:
```bash
./risk-game
```

## Contribución
Las contribuciones son bienvenidas. Por favor, abre un *issue* o un *pull request* para discutir cualquier cambio importante.
