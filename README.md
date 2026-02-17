<div align="center">
	<h1>Cub3D - Raycasting Engine 🎮</h1>

![42 School](https://img.shields.io/badge/42-School-000000?style=for-the-badge&logo=42&logoColor=white)
![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![OpenGL](https://img.shields.io/badge/MLX42-5586A4?style=for-the-badge&logo=opengl&logoColor=white)

**Un motor de raycasting 3D inspirado en Wolfenstein 3D**

[Características](#-características) • [Instalación](#-instalación) • [Uso](#-uso) • [Desarrollo](#-desarrollo)

</div>

[🇬🇧 English](README_EN.md) | [🇪🇸 Español](README.md)
---

## 📖 Descripción del Proyecto

Cub3D es un proyecto de 42 School que implementa un motor gráfico 3D desde cero utilizando la técnica de raycasting. Transforma un mapa 2D en una representación 3D navegable en tiempo real, con texturas en paredes, colores en suelos/techos y sistema completo de colisiones.

### 🎯 Aprendizajes Clave

- **Comprensión profunda de matemáticas aplicadas**: Vectores, trigonometría, geometría 2D/3D
- **Algoritmos de renderizado**: Implementación del algoritmo DDA (Digital Differential Analyzer)
- **Gestión de eventos y tiempo real**: Manejo de input del usuario y rendering continuo
- **Parsing y validación**: Procesamiento robusto de archivos de configuración
- **Gestión de memoria**: Control total sobre allocations, prevención de memory leaks
- **Trabajo con librerías gráficas**: Integración de MLX42 (MiniLibX evolution)

---

## 🚀 Características Principales

### ✨ Requisitos Implementados

- ✅ **Raycasting 3D completo** con proyección en perspectiva
- ✅ **Sistema de texturas** para las 4 direcciones (N/S/E/W)
- ✅ **Colores configurables** para suelo y techo (RGB)
- ✅ **Movimiento de jugador** Movimiento fluido (WASD) + rotación (←/→)
- ✅ **Sistema de colisiones** Detección y comprobación de la posición del jugador
- ✅ **Parsing exhaustivo** del archivo `.cub` con validación completa
- ✅ **Gestión de errores** robusta con mensajes descriptivos
- ✅ **Sin memory leaks** (validado con Valgrind)

### 🌟 Características Adicionales

- 🌟 **Minimapa en tiempo real** con transparencia (alpha blending manual)
- 🌟 **Sistema de colisiones mejorado** con margen/hitbox de jugador de 0.2 unidades
- 🌟 **Detección de esquinas** para evitar clipping diagonal
- 🌟 **Deslizamiento por paredes** (wall sliding) para movimiento natural

---

## 📁 Arquitectura del Proyecto

```
cub3d/
├── src/
│   ├── exec/          # Motor de renderizado y gameplay
│   │   ├── raycasting.c      # Algoritmo DDA y proyección
│   │   ├── raycasting2.c     # Cálculos de texturas
│   │   ├── render.c          # Loop principal de rendering
│   │   ├── moves.c           # Sistema de movimiento con colisiones
│   │   ├── rotate.c          # Rotación de cámara
│   │   ├── draw_map.c        # Minimapa con transparencia
│   │   ├── draw_utils.c      # Alpha blending
│   │   └── textures.c        # Carga y gestión de texturas
│   ├── parse/         # Validación y parsing del .cub
│   │   ├── parse_file.c      # Orquestación del parsing
│   │   ├── parse_map.c       # Validación del mapa
│   │   ├── parse_textures.c  # Validación de rutas PNG
│   │   ├── parse_colors.c    # Validación RGB
│   │   └── map_validation.c  # Comprobación de bordes
│   ├── init/          # Inicialización de estructuras
│   └── free/          # Gestión de memoria
├── maps/
│   ├── success/       # 6 mapas válidos
│   └── failure/       # 20 casos de error
├── inc/
│   └── cub3d.h        # Header principal
├── lib/
│   ├── libft/         # Librería de utilidades
│   └── MLX42/         # Librería gráfica
└── test_maps.sh       # Testing automatizado
```
---

## 🔄 Evolución del Desarrollo

### Fase 1: Parsing y Validación

**Problemas resueltos:**
- ✅ Parsing de archivos `.cub` con formato flexible
- ✅ Validación de texturas (existencia, extensión `.png`)
- ✅ Validación RGB (rango 0-255, sin duplicados)
- ✅ Detección de mapas no cerrados (flood fill)
- ✅ Gestión de líneas vacías dentro del mapa

### Fase 2: Renderizado Básico

**Problemas resueltos:**
- ✅ Implementación del algoritmo DDA
- ✅ Proyección de paredes en perspectiva
- ✅ Cálculo de alturas de línea (line_height)
- ✅ Prevención de división por cero en delta_dist

### Fase 3: Texturas y Movimiento

**Problemas resueltos:**
- ✅ Carga de texturas PNG con MLX42
- ✅ Mapeo de texturas a coordenadas de pared (wall_x, tex_x)
- ✅ Sistema de colisiones básico
- ✅ Bug de clipping en esquinas (diagonal movement)

### Fase 4: Testing y Refinamiento

**Problemas resueltos:**
- ✅ 20 casos de error documentados y testeados
- ✅ Mensajes de error únicos (no duplicados)
- ✅ Validación con Valgrind (0 leaks)
- ✅ Cumplimiento de Norminette

### Fase 5: Mejoras Visuales

**Problemas resueltos:**
- ✅ **Alpha blending manual** (MLX42 no soporta transparencia nativa)
- ✅ Minimapa con colores semi-transparentes
- ✅ Refactorización de funciones de dibujado
- ✅ Sistema de colisiones con margen (0.2 unidades)
- ✅ Deslizamiento por paredes

---

## 🐛 Desafíos Técnicos Resueltos

### 1. Alpha Blending en MLX42
**Problema:** MLX42 ignora el canal alpha en `mlx_put_pixel()`.

**Solución implementada:**
```c
// Lectura del píxel de fondo
uint32_t bg_color = get_pixel(img, x, y);

// Fórmula de blending manual
r_final = (r_fg × alpha + r_bg × (255-alpha)) / 255;
g_final = (g_fg × alpha + g_bg × (255-alpha)) / 255;
b_final = (b_fg × alpha + b_bg × (255-alpha)) / 255;

// Escritura del píxel mezclado (opaco)
mlx_put_pixel(img, x, y, r_final << 24 | g_final << 16 | b_final << 8 | 0xFF);
```

**Resultado:** Minimapa semi-transparente sobre la escena 3D.

### 2. Clipping en Esquinas Diagonales
**Problema:** El jugador podía atravesar esquinas al moverse diagonalmente a alta velocidad.

**Causa:** Validación separada de X e Y permitía movimiento diagonal incluso con pared en la esquina.

**Solución:**
```c
// 1. Verificar las 4 esquinas del jugador con margen
if (is_valid_position(game, new_x, new_y, margin))
    move_diagonal();
else {
    // 2. Si falla, intentar deslizamiento
    if (is_valid_position(game, player.x, new_y, margin))
        move_y_only();
    if (is_valid_position(game, new_x, player.y, margin))
        move_x_only();
}
```

### 3. Errores Duplicados en RGB
**Problema:** Valores RGB inválidos mostraban 3 mensajes de error (uno por canal).

**Solución:**
- Retorno inmediato en `parse_rgb()` al primer error
- Validación de color completo antes de continuar
- Mensaje único y descriptivo

### 4. División por Cero en Raycasting
**Problema:** `ray_dir_x = 0` o `ray_dir_y = 0` causaba división por cero en `calc_delta_dist()`.

**Solución:**
```c
if (ray->ray_dir_x == 0)
    ray->delta_dist_x = 1e30;  // Infinito
else
    ray->delta_dist_x = fabs(1.0 / ray->ray_dir_x);
```

### 5. Líneas Vacías en el Mapa
**Problema:** GNL + split eliminaba líneas vacías dentro del mapa, rompiendo la geometría.

**Solución:**
- Nueva implementación Split
- Preservar líneas vacías como strings vacíos `""`
- Rellenar con espacios las líneas cortas

---

## 🧪 Testing y Validación

**Cobertura:**
- ✅ 20 mapas de error (failure/) y mapas válidos (success/)
- ✅ Validación con Valgrind

**Casos de error testeados:**
1. Archivo vacío
2. Sin jugador / Múltiples jugadores
3. Texturas faltantes / Extensión incorrecta
4. Colores inválidos / Duplicados
5. Mapa no cerrado (top, bottom, left, right)
6. Caracteres inválidos
7. Líneas vacías en el mapa
8. Zonas desconectadas

### Validación de Memoria
```bash
valgrind --leak-check=full ./cub3d maps/success/map1.cub
```
---

## 💻 Instalación

### Prerrequisitos
```bash
# Ubuntu/Debian
sudo apt-get install build-essential libglfw3-dev


### Compilación
```bash
git clone https://github.com/eduaserr/cub3d.git
cd cub3d
make
```

### Ejecución
```bash
./cub3d maps/success/map1.cub
```

---

## 🎮 Controles

| Tecla | Acción |
|-------|--------|
| `W` | Avanzar |
| `S` | Retroceder |
| `A` | Moverse a la izquierda |
| `D` | Moverse a la derecha |
| `←` | Rotar cámara izquierda |
| `→` | Rotar cámara derecha |
| `ESC` | Salir |

---

## 📝 Formato del Archivo .cub

```
NO ./textures/north_texture.png
SO ./textures/south_texture.png
WE ./textures/west_texture.png
EA ./textures/east_texture.png

F 220,100,0
C 225,30,0

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

**Reglas de validación:**
- Identificadores: `NO`, `SO`, `WE`, `EA`, `F`, `C`
- Texturas: extensión `.png` obligatoria
- RGB: valores entre 0-255, formato `R,G,B`
- Mapa: caracteres válidos `0`, `1`, `N`, `S`, `E`, `W`, espacios
- Un solo jugador con orientación (`N`/`S`/`E`/`W`)
- Mapa cerrado por paredes (`1`)

---

## 🏗️ Algoritmo de Raycasting

### Flujo del Algoritmo DDA

```
Para cada columna x de la pantalla (0 a WIDTH):
  1. init_ray()          → Inicializar rayo con dirección
  2. calc_delta_dist()   → Calcular distancia entre grid intersections
  3. calc_step_side()    → Determinar dirección de paso (+1 o -1)
  4. exec_dda()          → Ejecutar DDA hasta encontrar pared
     └─ while (!hit)
        ├─ Avanzar al siguiente grid
        └─ Comprobar si es pared
  5. calc_wall_dist()    → Calcular distancia perpendicular
  6. calc_line_height()  → Determinar altura de línea a dibujar
  7. init_texture_vars() → Configurar coordenadas de textura
  8. draw_vertical_line()→ Dibujar columna de píxeles con textura
```

### Fórmulas Clave

*Posición del rayo*

*Distancia entre intersecciones*

*Distancia perpendicular (sin fish-eye)*

*Altura de línea*

---

## 🎨 Sistema de Renderizado

### Orden de Dibujado

```
1. draw_background()  → Suelo y techo (colores sólidos)
   └─ Top half: ceiling color
   └─ Bottom half: floor color

2. raycasting()       → Paredes 3D con texturas
   └─ draw_vertical_line() para cada columna

3. draw_map()         → Minimapa con alpha blending
   └─ draw_cell() con transparencia
   └─ draw_player() con color opaco
```

### Performance
- **Optimizaciones:**
  - DDA eficiente (solo integers en loop)
  - Texturas pre-cargadas en memoria
  - Sin cálculos redundantes por frame

---

## 👥 Colaboradores

| Nombre | GitHub | Contribuciones |
|--------|--------|----------------|
| **eduaserr** | [@eduaserr](https://github.com/eduaserr) | Parsing, validación, testing |
| **pruiz-al** | [@pruiz-al](https://github.com/pruiz-al) | Raycasting, texturas, colisiones, rendering |

---

## 📚 Recursos y Referencias

### Documentación Técnica
- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html) - Tutorial fundamental
- [MLX42 Documentation](https://github.com/codam-coding-college/MLX42) - Librería gráfica

### Conceptos Matemáticos
- [DDA Algorithm](https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm))
- [Bresenham's Line Algorithm](https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm)
- [Vector Mathematics](https://www.khanacademy.org/math/linear-algebra/vectors-and-spaces)

---

## 📄 Licencia

Este proyecto es parte del curriculum de 42 School y está destinado únicamente para fines educativos.

---

<div align="center">

**Hecho con ❤️ y mucho ☕ en 42 School**

⭐ Si te gustó el proyecto, considera darle una estrella

</div>
