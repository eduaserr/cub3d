

## Análisis del Raycasting

raycasting() → para cada pixel x de pantalla
  ├─ init_ray() → inicializa el rayo
  ├─ calc_delta_dist() → distancia entre grid intersections
  ├─ calc_step_side() → dirección y distancia inicial
  ├─ exec_dda() → algoritmo DDA (busca pared)
  ├─ calc_wall_dist() → distancia a la pared
  ├─ calc_line_height() → altura de la línea a dibujar
  ├─ init_texture_vars() → configura textura
  └─ draw_vertical_line() → dibuja columna de píxeles