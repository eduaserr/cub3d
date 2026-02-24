*This project has been created as part of the 42 curriculum by eduaserr, pruiz-al*

<div align="center">
	<h1>Cub3D - Raycasting Engine 🎮</h1>

![42 School](https://img.shields.io/badge/42-School-000000?style=for-the-badge&logo=42&logoColor=white)
![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![OpenGL](https://img.shields.io/badge/MLX42-5586A4?style=for-the-badge&logo=opengl&logoColor=white)

**A 3D raycasting engine inspired by Wolfenstein 3D**

</div>

[🇪🇸 Español](README.md) | [🇬🇧 English](README_EN.md)

---

## 📑 Table of Contents

1. [📖 Project Description](#-project-description)
2. [🚀 Main Features](#-main-features)
3. [📁 Project Architecture](#-project-architecture)
4. [🔄 Development Evolution](#-development-evolution)
5. [🐛 Resolved Technical Challenges](#-resolved-technical-challenges)
6. [🧪 Testing and Validation](#-testing-and-validation)
7. [💻 Installation](#-installation)
8. [🎮 Controls](#-controls)
9. [📝 .cub File Format](#-cub-file-format)
10. [🏗️ Raycasting Algorithm](#️-raycasting-algorithm)
11. [🎨 Rendering System](#-rendering-system)
12. [👥 Contributors](#-contributors)
13. [📚 Resources and References](#-resources-and-references)
14. [📄 License](#-license)

---

## 📖 Project Description

Cub3D is a 42 School project that implements a 3D graphics engine from scratch using the raycasting technique. It transforms a 2D map into a navigable 3D representation in real-time, with wall textures, floor/ceiling colors, and a complete collision system.

### 🎯 Key Learnings

- **Deep understanding of applied mathematics**: Vectors, trigonometry, 2D/3D geometry
- **Rendering algorithms**: Implementation of the DDA (Digital Differential Analyzer) algorithm
- **Event and real-time management**: Handling user input and continuous rendering
- **Parsing and validation**: Robust processing of configuration files
- **Memory management**: Full control over allocations, memory leak prevention
- **Working with graphics libraries**: Integration of MLX42 (MiniLibX evolution)

---

## 🚀 Main Features

### ✨ Implemented Requirements

- ✅ **Complete 3D raycasting** with perspective projection
- ✅ **Texture system** for all 4 directions (N/S/E/W)
- ✅ **Configurable colors** for floor and ceiling (RGB)
- ✅ **Player movement** Smooth movement (WASD) + rotation (←/→)
- ✅ **Collision system** Player position detection and verification
- ✅ **Exhaustive parsing** of `.cub` file with complete validation
- ✅ **Robust error handling** with descriptive messages
- ✅ **No memory leaks** (validated with Valgrind)

### 🌟 Additional Features

- 🌟 **Real-time minimap** with transparency (manual alpha blending)
- 🌟 **Enhanced collision system** with player margin/hitbox of 0.2 units
- 🌟 **Corner detection** to avoid diagonal clipping
- 🌟 **Wall sliding** for natural movement

---

## 📁 Project Architecture

```
cub3d/
├── src/
│   ├── exec/          # Rendering engine and gameplay
│   │   ├── raycasting.c      # DDA algorithm and projection
│   │   ├── raycasting2.c     # Texture calculations
│   │   ├── render.c          # Main rendering loop
│   │   ├── moves.c           # Movement system with collisions
│   │   ├── rotate.c          # Camera rotation
│   │   ├── draw_map.c        # Minimap with transparency
│   │   ├── draw_utils.c      # Alpha blending
│   │   └── textures.c        # Texture loading and management
│   ├── parse/         # .cub validation and parsing
│   │   ├── parse_file.c      # Parsing orchestration
│   │   ├── parse_map.c       # Map validation
│   │   ├── parse_textures.c  # PNG path validation
│   │   ├── parse_colors.c    # RGB validation
│   │   └── map_validation.c  # Border checking
│   ├── init/          # Structure initialization
│   └── free/          # Memory management
├── maps/
│   ├── success/       # 6 valid maps
│   └── failure/       # 20 error cases
├── inc/
│   └── cub3d.h        # Main header
├── lib/
│   ├── libft/         # Utility library
│   └── MLX42/         # Graphics library
└── test_maps.sh       # Automated testing
```
---

## 🔄 Development Evolution

### Phase 1: Parsing and Validation

**Problems solved:**
- ✅ Parsing of `.cub` files with flexible format
- ✅ Texture validation (existence, `.png` extension)
- ✅ RGB validation (0-255 range, no duplicates)
- ✅ Detection of unclosed maps (flood fill)
- ✅ Management of empty lines within the map

### Phase 2: Basic Rendering

**Problems solved:**
- ✅ Implementation of DDA algorithm
- ✅ Perspective wall projection
- ✅ Line height calculation (line_height)
- ✅ Prevention of division by zero in delta_dist

### Phase 3: Textures and Movement

**Problems solved:**
- ✅ Loading PNG textures with MLX42
- ✅ Texture mapping to wall coordinates (wall_x, tex_x)
- ✅ Basic collision system
- ✅ Corner clipping bug (diagonal movement)

### Phase 4: Testing and Refinement

**Problems solved:**
- ✅ 20 documented and tested error cases
- ✅ Unique error messages (no duplicates)
- ✅ Validation with Valgrind (0 leaks)
- ✅ Norminette compliance
- ✅ Tabs not suported inside map

### Phase 5: Visual Improvements

**Problems solved:**
- ✅ **Manual alpha blending** (MLX42 doesn't support native transparency)
- ✅ Minimap with semi-transparent colors
- ✅ Refactoring of drawing functions
- ✅ Collision system with margin (0.2 units)
- ✅ Wall sliding

---

## 🐛 Resolved Technical Challenges

### 1. Alpha Blending in MLX42
**Problem:** MLX42 ignores the alpha channel in `mlx_put_pixel()`.

**Implemented solution:**
```c
// Background pixel reading
uint32_t bg_color = get_pixel(img, x, y);

// Manual blending formula
r_final = (r_fg × alpha + r_bg × (255-alpha)) / 255;
g_final = (g_fg × alpha + g_bg × (255-alpha)) / 255;
b_final = (b_fg × alpha + b_bg × (255-alpha)) / 255;

// Write blended pixel (opaque)
mlx_put_pixel(img, x, y, r_final << 24 | g_final << 16 | b_final << 8 | 0xFF);
```

**Result:** Semi-transparent minimap over the 3D scene.

### 2. Diagonal Corner Clipping
**Problem:** Player could pass through corners when moving diagonally at high speed.

**Cause:** Separate X and Y validation allowed diagonal movement even with a corner wall.

**Solution:**
```c
// 1. Check the 4 player corners with margin
if (is_valid_position(game, new_x, new_y, margin))
    move_diagonal();
else {
    // 2. If it fails, try sliding
    if (is_valid_position(game, player.x, new_y, margin))
        move_y_only();
    if (is_valid_position(game, new_x, player.y, margin))
        move_x_only();
}
```

### 3. Duplicate RGB Errors
**Problem:** Invalid RGB values showed 3 error messages (one per channel).

**Solution:**
- Immediate return in `parse_rgb()` at first error
- Complete color validation before continuing
- Unique and descriptive message

### 4. Division by Zero in Raycasting
**Problem:** `ray_dir_x = 0` or `ray_dir_y = 0` caused division by zero in `calc_delta_dist()`.

**Solution:**
```c
if (ray->ray_dir_x == 0)
    ray->delta_dist_x = 1e30;  // Infinity
else
    ray->delta_dist_x = fabs(1.0 / ray->ray_dir_x);
```

### 5. Empty Lines in the Map
**Problem:** GNL + split removed empty lines within the map, breaking the geometry.

**Solution:**
- New Split implementation
- Preserve empty lines as empty strings `""`
- Fill short lines with spaces

---

## 🧪 Testing and Validation

**Coverage:**
- ✅ 20 error maps (failure/) and valid maps (success/)
- ✅ Validation with Valgrind

**Tested error cases:**
1. Empty file
2. No player / Multiple players
3. Missing textures / Incorrect extension
4. Invalid colors / Duplicates
5. Unclosed map (top, bottom, left, right)
6. Invalid characters
7. Empty lines in the map
8. Disconnected zones

### Memory Validation
```bash
valgrind --leak-check=full ./cub3d maps/success/map1.cub
```
---

## 💻 Installation

### Prerequisites
```bash
# Ubuntu/Debian
sudo apt-get install build-essential libglfw3-dev
```

### Compilation
```bash
git clone https://github.com/eduaserr/cub3d.git
cd cub3d
make
```

### Execution
```bash
./cub3d maps/success/map1.cub
```

---

## 🎮 Controls

| Key | Action |
|-------|--------|
| `W` | Move forward |
| `S` | Move backward |
| `A` | Move left |
| `D` | Move right |
| `←` | Rotate camera left |
| `→` | Rotate camera right |
| `ESC` | Exit |

---

## 📝 .cub File Format

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

**Validation rules:**
- Identifiers: `NO`, `SO`, `WE`, `EA`, `F`, `C`
- Textures: `.png` extension mandatory
- RGB: values between 0-255, format `R,G,B`
- Map: valid characters `0`, `1`, `N`, `S`, `E`, `W`, spaces
- Single player with orientation (`N`/`S`/`E`/`W`)
- Map closed by walls (`1`)

---

## 🏗️ Raycasting Algorithm

### DDA Algorithm Flow

```
For each column x of the screen (0 to WIDTH):
  1. init_ray()          → Initialize ray with direction
  2. calc_delta_dist()   → Calculate distance between grid intersections
  3. calc_step_side()    → Determine step direction (+1 or -1)
  4. exec_dda()          → Execute DDA until finding wall
     └─ while (!hit)
        ├─ Advance to next grid
        └─ Check if it's a wall
  5. calc_wall_dist()    → Calculate perpendicular distance
  6. calc_line_height()  → Determine line height to draw
  7. init_texture_vars() → Configure texture coordinates
  8. draw_vertical_line()→ Draw pixel column with texture
```

### Key Formulas

*Ray position*

*Distance between intersections*

*Perpendicular distance (no fish-eye)*

*Line height*

---

## 🎨 Rendering System

### Drawing Order

```
1. draw_background()  → Floor and ceiling (solid colors)
   └─ Top half: ceiling color
   └─ Bottom half: floor color

2. raycasting()       → 3D walls with textures
   └─ draw_vertical_line() for each column

3. draw_map()         → Minimap with alpha blending
   └─ draw_cell() with transparency
   └─ draw_player() with opaque color
```

### Performance
- **Optimizations:**
  - Efficient DDA (only integers in loop)
  - Pre-loaded textures in memory
  - No redundant calculations per frame

---

## 👥 Contributors

| Name | GitHub | Contributions |
|--------|--------|----------------|
| **eduaserr** | [@eduaserr](https://github.com/eduaserr) | Parsing, validation, testing, documentation |
| **pruiz-al** | [@pruiz-al](https://github.com/pruiz-al) | Raycasting, textures, collisions, rendering |

---

## 📚 Resources and References

### Technical Documentation
- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html) - Fundamental tutorial
- [MLX42 Documentation](https://github.com/codam-coding-college/MLX42) - Graphics library

### Mathematical Concepts
- [DDA Algorithm](https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm))
- [Bresenham's Line Algorithm](https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm)
- [Vector Mathematics](https://www.khanacademy.org/math/linear-algebra/vectors-and-spaces)

---

## 📄 License

This project is part of the 42 School curriculum and is intended for educational purposes only.

---

<div align="center">

**Made with ❤️ and lots of ☕ at 42 School**

⭐ If you liked the project, consider giving it a star

</div>
