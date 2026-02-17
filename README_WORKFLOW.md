## 📁 Estructura del Proyecto

```
cub3d/
├── inc/
│   └── cub3d.h                 # Header principal con estructuras y prototipos
├── lib/
│   ├── libft/                  # Librería libft
│   └── MLX42/                  # Librería gráfica MLX42
├── maps/
│   ├── success/                # Mapas válidos para testing
│   └── failure/                # Mapas de error para testing
├── src/
│   ├── exec/                   # Lógica de ejecución del juego
│   │   ├── raycasting.c        # Algoritmo de raycasting
│   │   ├── raycasting2.c       # Funciones auxiliares de raycasting
│   │   ├── render.c            # Loop de renderizado
│   │   ├── moves.c             # Sistema de movimiento del jugador
│   │   ├── rotate.c            # Rotación de cámara
│   │   ├── draw_map.c          # Minimapa con transparencia
│   │   └── draw_utils.c        # Utilidades de dibujado (alpha blending)
│   ├── free/
│   │   └── free.c              # Liberación de memoria
│   ├── init/
│   │   ├── init.c              # Inicialización de valores
│   │   ├── init_mlx.c          # Inicialización de MLX42
│   │   └── init_player.c       # Inicialización del jugador
│   └── parse/
│       ├── find_map.c          # Encuentra inicio del mapa
│       ├── parse_colors.c      # Parseo de colores RGB
│       ├── parse_file.c        # Validación general del archivo
│       ├── parse_map.c         # Validación del mapa
│       ├── parse_textures.c    # Parseo de rutas de texturas
│       └── read_map.c          # Lectura del archivo .cub
├── textures/                   # Texturas del juego
│   ├── NO.png                  # Textura norte
│   ├── SO.png                  # Textura sur
│   ├── EA.png                  # Textura este
│   └── WE.png                  # Textura oeste
├── Makefile
├── main.c                      # Punto de entrada
├── test_maps.sh                # Script de testing automático
└── README.md
```

## 🔄 Flujo de Ejecución

```
┌─────────────────────────────────────────────────────────────────┐
│                          MAIN (main.c)                          │
└───────────────────────────────┬─────────────────────────────────┘
                                │
                    ┌───────────┴───────────┬───────────────────────────────────────────────────────────┐
                    │  Validación de args   │															│
                    │  check_extension()    │															│
                    └───────────┬───────────┘															│
                                │																		│
                    ┌───────────▼───────────┬───────────────────────────────────────────────────────────┤
                    │    get_file()         │															│
                    │  (Parse del .cub)     │															│
                    └───────────┬───────────┘															│
                                │																		│
        ┌───────────────────────┼───────────────────────┬───────────────────────────────────────────────┤
        │                       │                       │												│
        ▼                       ▼                       ▼												│
┌───────────────┐   ┌───────────────────┐    ┌─────────────────┐										│
│ init_values() │   │   read_map()      │    │  parse_file()   │										│
│               │   │ (Lee archivo)     │    │ (Valida todo)   │										│
└───────────────┘   └───────────────────┘    └────────┬────────┘										│
                                                      │													│
                        ┌─────────────────────────────┼─────────────────────────────┬───────────────────┤
                        │                             │                             │					│
                        ▼                             ▼                             ▼					│
                ┌───────────────┐           ┌─────────────────┐         ┌─────────────────┐				│
                │get_sidetxt()  │           │  get_colors()   │         │   get_map()     │				│
                │(Texturas)     │           │  (Floor/Ceil)   │         │ (Validación)    │				│
                └───────────────┘           └─────────────────┘         └─────────────────┘				│
                                                      │													│
                                        ┌─────────────┴─────────────┬───────────────────────────────────┤
                                        │                           │									│
                                        ▼                           ▼									▼
                                ┌───────────────┐         ┌──────────────────┐					┌───────────────────────┐
                                │check_borders()│         │check_characters()│					│  ft_error()			│
                                │(Paredes)      │         │(Validez chars)   │					│ (Salida del programa) │
                                └───────────────┘         └──────────────────┘					└───────────────────────┘
                                                      │
                                        ┌─────────────▼─────────────┐
                                        │        exec()             │
                                        │   (Ejecución del juego)   │
                                        └─────────────┬─────────────┘
                                                      │
                        ┌─────────────────────────────┼─────────────────────────────┐
                        │                             │                             │
                        ▼                             ▼                             ▼
                ┌───────────────┐           ┌─────────────────┐         ┌─────────────────┐
                │init_player()  │           │   init_mlx()    │         │init_textures()  │
                │(Posición/Dir) │           │(Ventana/Imagen) │         │(Carga PNGs)     │
                └───────────────┘           └─────────────────┘         └─────────────────┘
                                                      │
                                        ┌─────────────▼─────────────┐
                                        │      mlx_loop()           │
                                        │   (Bucle infinito)        │
                                        └─────────────┬─────────────┘
                                                      │
                                                      │ [Cada frame]
                                                      │
                                        ┌─────────────▼─────────────┐
                                        │       render()            │
                                        │ (Hook de renderizado)     │
                                        └─────────────┬─────────────┘
                                                      │
                                ┌─────────────────────┼─────────────────────┐
                                │                     │                     │
                                ▼                     ▼                     ▼
                        ┌───────────────┐     ┌──────────────┐    ┌──────────────┐
                        │ raycasting()  │     │ draw_map()   │    │player_input()│
                        │ (Dibuja 3D)   │     │(Minimapa)    │    │(Movimiento)  │
                        └───────────────┘     └──────────────┘    └──────────────┘
                                │
                ┌───────────────┼───────────────┐
                │               │               │
                ▼               ▼               ▼
        ┌──────────┐    ┌──────────┐   ┌──────────────┐
        │init_ray()│    │exec_dda()│   │draw_vertical │
        │          │    │(Colisión)│   │   _line()    │
        └──────────┘    └──────────┘   └──────────────┤
                                                      │
                                        [ESC pressed] │
                                                      │
                                        ┌─────────────▼─────────────┐
                                        │      free_all()           │
                                        │   (Libera memoria)        │
                                        └───────────────────────────┘
```
