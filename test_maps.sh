#!/bin/bash

# Script de prueba para cub3D
# Prueba todos los mapas de error y éxito

set -e

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

PASSED=0
FAILED=0
TOTAL=0

# Carpetas de mapas
FAILURE_MAPS="maps/failure"
SUCCESS_MAPS="maps/success"

echo "================================"
echo "   CUB3D MAP TEST SUITE"
echo "================================"
echo ""

# Compilar
echo -e "${YELLOW}Compilando cub3D...${NC}"
make clean > /dev/null 2>&1 || true
make > /dev/null 2>&1
if [ ! -f ./cub3D ]; then
    echo -e "${RED}Error: No se pudo compilar cub3D${NC}"
    exit 1
fi
echo -e "${GREEN}Compilación exitosa${NC}"
echo ""

# Función para probar un mapa de error CON VALGRIND
test_failure_map() {
    local map=$1
    local description=$2
    TOTAL=$((TOTAL + 1))
    
    # Ejecutar con valgrind
    if valgrind --leak-check=full ./cub3D "$map" > /dev/null 2>&1; then
        echo -e "${RED}[FAIL]${NC} $description"
        echo "       Esperaba error pero el programa ejecutó exitosamente"
        FAILED=$((FAILED + 1))
        return 1
    else
        echo -e "${GREEN}[PASS]${NC} $description"
        PASSED=$((PASSED + 1))
        return 0
    fi
}

# Función para probar un mapa de éxito SIN VALGRIND
test_success_map() {
    local map=$1
    local description=$2
    TOTAL=$((TOTAL + 1))
    
    # Ejecutar el programa y capturar el código de salida
    # Como los mapas de éxito lanzan la ventana MLX, usamos timeout
    if timeout 1 ./cub3D "$map" > /dev/null 2>&1; then
        echo -e "${GREEN}[PASS]${NC} $description"
        PASSED=$((PASSED + 1))
        return 0
    else
        # Timeout es código 124, pero el programa se ejecutó (debería ser error)
        if [ $? -eq 124 ]; then
            echo -e "${GREEN}[PASS]${NC} $description (timeout en MLX - esperado)"
            PASSED=$((PASSED + 1))
            return 0
        else
            echo -e "${RED}[FAIL]${NC} $description"
            echo "       El programa debería ejecutarse exitosamente"
            FAILED=$((FAILED + 1))
            return 1
        fi
    fi
}

echo "======== PRUEBAS DE MAPAS DE ERROR (con Valgrind) ========"
echo ""

# Pruebas de texturas faltantes
test_failure_map "$FAILURE_MAPS/missing_texture_north.cub" "Textura NORTE faltante"

echo ""

# Pruebas de colores
test_failure_map "$FAILURE_MAPS/missing_ceiling_color.cub" "Color de techo faltante"
test_failure_map "$FAILURE_MAPS/invalid_ceiling_color.cub" "Color de techo inválido (RGB > 255)"
test_failure_map "$FAILURE_MAPS/duplicate_floor_rgb.cub" "Color de piso duplicado"

echo ""

# Pruebas de jugador
test_failure_map "$FAILURE_MAPS/no_player.cub" "Sin jugador en el mapa"
test_failure_map "$FAILURE_MAPS/multiple_players.cub" "Múltiples jugadores en el mapa"

echo ""

# Pruebas de validación de mapa
test_failure_map "$FAILURE_MAPS/invalid_character_in_map.cub" "Carácter inválido en el mapa"
test_failure_map "$FAILURE_MAPS/map_not_closed_top.cub" "Mapa no cerrado (arriba)"
test_failure_map "$FAILURE_MAPS/map_not_closed_bottom.cub" "Mapa no cerrado (abajo)"
test_failure_map "$FAILURE_MAPS/map_not_closed_left.cub" "Mapa no cerrado (izquierda)"
test_failure_map "$FAILURE_MAPS/map_not_closed_right.cub" "Mapa no cerrado (derecha)"

echo ""

# Pruebas de edge cases
test_failure_map "$FAILURE_MAPS/empty_file.cub" "Archivo vacío"
test_failure_map "$FAILURE_MAPS/empty_map.cub" "Mapa vacío"
test_failure_map "$FAILURE_MAPS/empty_line_in_map.cub" "Línea vacía dentro del mapa"
test_failure_map "$FAILURE_MAPS/inverted_map.cub" "Mapa invertido (configuración después del mapa)"
test_failure_map "$FAILURE_MAPS/missing_extension" "Archivo sin extensión .cub"
test_failure_map "$FAILURE_MAPS/missing_png_extension.cub" "Textura sin extensión .png"
test_failure_map "$FAILURE_MAPS/disconnected_zones.cub" "Zonas desconectadas en el mapa"

echo ""
echo "======== PRUEBAS DE MAPAS DE ÉXITO (sin Valgrind) ========"
echo ""

# Pruebas de mapas válidos
test_success_map "$SUCCESS_MAPS/simple_map_east.cub" "Mapa simple - Jugador mirando ESTE"
test_success_map "$SUCCESS_MAPS/complex_map_east.cub" "Mapa complejo"
test_success_map "$SUCCESS_MAPS/map1.cub" "Mapa básico"

echo ""
echo "================================"
echo "   RESULTADOS FINALES"
echo "================================"
echo "Total de pruebas: $TOTAL"
echo -e "${GREEN}Pasadas: $PASSED${NC}"
echo -e "${RED}Fallidas: $FAILED${NC}"

if [ $FAILED -eq 0 ]; then
    echo -e "${GREEN}✓ TODAS LAS PRUEBAS PASARON${NC}"
    exit 0
else
    echo -e "${RED}✗ ALGUNAS PRUEBAS FALLARON${NC}"
    exit 1
fi