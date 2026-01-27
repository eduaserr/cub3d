/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduaserr <eduaserr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 03:22:08 by eduaserr          #+#    #+#             */
/*   Updated: 2026/01/27 16:54:04 by eduaserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <time.h>
# include <stdio.h>
# include "../lib/libft/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"

# define WIN_WIDTH 1024
# define WIN_HEIGHT 768
# define CELL_SIZE 20
# define PLAYER_SIZE 10

enum dir
{
	NORTH = 0,
	SOUTH,
	EAST,
	WEST
};

enum rgb
{
	F = 0,
	C = 1,
};

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_parser
{
	char	*imgsidewall[4];
	t_color	rgb[2];
}		t_parser;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}		t_player;

typedef struct s_map
{
	char		**file;
	char		**cpyfile;
	char		**map;
	int			width;
	int			length;
	int			player;
	int			floor;
	int			wall;

	//t_player	player_pos;
	//t_exit		exit_pos;
}		t_map;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	void		*window;
	t_parser	parser;
	t_map		map;
	t_player	player;
}		t_game;


/* ************************************************************************** */
/*                                  MAIN                                      */
/* ************************************************************************** */

/**
 * @brief Checks if a file has the correct extension.
 * Validates that the filename ends with the specified extension.
 * 
 * @param av Filename to check
 * @param str Expected extension (e.g., ".cub", ".png")
 * @return 0 if extension is valid, 1 if invalid or filename too short
 */
int	check_extension(char *av, char *str);

/* ************************************************************************** */
/*                                  FREE                                      */
/* ************************************************************************** */

/**
 * @brief Frees all parser-related memory.
 * Releases memory allocated for texture paths in the parser structure.
 * 
 * @param game Pointer to game structure
 */
void	free_parser(t_game *game);

/**
 * @brief Frees all allocated memory in the game structure.
 * Releases parser data, map data, and any other allocated resources.
 * 
 * @param game Pointer to game structure
 */
void	free_all(t_game *game);

/* ************************************************************************** */
/*                                  INIT                                      */
/* ************************************************************************** */

/**
 * @brief Initializes all game structure values to default/zero.
 * Sets all pointers to NULL and numeric values to 0 or -1 as needed.
 * 
 * @param game Pointer to game structure
 */
void	init_values(t_game *game);

/**
 * @brief Initializes player position and orientation.
 * Sets up player coordinates, direction vector, and camera plane.
 * 
 * @param game Pointer to game structure
 */
void	init_player(t_game *game);

/**
 * @brief Initializes MLX library and creates window.
 * Sets up the graphics library and creates the game window.
 * 
 * @param game Pointer to game structure
 */
void	init_mlx(t_game *game);

/* ************************************************************************** */
/*                                  PARSE                                     */
/* ************************************************************************** */

/**
 * @brief Reads the map file and returns it as a string array.
 * Opens the file, reads all lines, and stores them in a NULL-terminated array.
 * 
 * @param file_map Path to the .cub map file
 * @return Array of strings containing file content, NULL on error
 */
char	**read_map(char *file_map);

/**
 * @brief Main parsing function that validates and processes the map file.
 * Calls all parsing subfunctions to extract textures, colors, and map data.
 * 
 * @param game Pointer to game structure
 * @param map Array of strings containing the map file content
 */
void	parse_file(t_game *game, char **map);

/**
 * @brief Parses and validates wall texture paths from the file.
 * Extracts NO, SO, WE, EA texture paths and validates their existence.
 * 
 * @param game Pointer to game structure
 * @param map Array of strings containing the map file content
 */
void	get_sidetxt(t_game *game, char **map);

/**
 * @brief Parses and validates floor and ceiling RGB colors.
 * Extracts F and C color values and validates RGB range (0-255).
 * 
 * @param game Pointer to game structure
 * @param map Array of strings containing the map file content
 */
void	get_colors(t_game *game, char **map);

/**
 * @brief Extracts the map grid from the file.
 * Identifies map boundaries and copies the map data to game structure.
 * 
 * @param game Pointer to game structure
 * @param file Array of strings containing the map file content
 */
void	get_map(t_game *game, char **file);

/**
 * @brief Finds the start and end indices of the map in the file.
 * Scans the file array to locate map boundaries.
 * 
 * @param file Array of strings containing the file content
 * @param i Pointer to store end index
 * @param j Pointer to store start index
 * @return 0 on success, -1 on error
 */
int		find_map(char **file, int *i, int *j);

/**
 * @brief Validates if a character is allowed in the map.
 * 
 * @param c Character to validate
 * @return 1 if valid, 0 if invalid
 */
int		valid_char(char c);

/**
 * @brief Checks if a line is empty or contains only spaces.
 * 
 * @param line Line to check
 * @return 1 if empty, 0 otherwise
 */
int		is_empty_line(char *line);

/**
 * @brief Determines if a line belongs to the map.
 * 
 * @param line Line to analyze
 * @return 1 if map line, 0 if not, -1 on error
 */
int		is_map_line(char *line);

/**
 * @brief Validates all characters in a map line.
 * 
 * @param line Line to validate
 * @return 1 if valid, 0 if invalid
 */
int		validate_line(char *line);

/**
 * @brief Identifies the type of configuration line.
 * Matches line identifier (NO, SO, WE, EA, F, C) with valid types.
 * 
 * @param line Line to analyze
 * @param sides Array of valid identifiers
 * @param len Number of valid identifiers
 * @return Index of matched type, or -1 if no match found
 */
int		get_type(char *line, char **sides, int len);

/**
 * @brief Extracts the file path from a configuration line.
 * Skips identifier and whitespace, returns the path string.
 * 
 * @param line Configuration line to parse
 * @return Allocated string containing the path, NULL on error
 */
char	*get_path(char *line);

/* ************************************************************************** */
/*                                   EXEC                                     */
/* ************************************************************************** */

/**
 * @brief Renders the game map on the window.
 * Draws walls, floor, ceiling, and other map elements.
 * 
 * @param game Pointer to game structure
 */
void	draw_map(t_game *game);

/* ************************************************************************** */
/*                                  PRINT                                     */
/* ************************************************************************** */

/**
 * @brief Displays an error message and terminates the program with exit().
 * All allocated memory must be freed before calling this function.
 * 
 * @param str Error message to display
 * @warning This function calls exit(EXIT_FAILURE). Free all resources before.
 */
void	ft_error(char *str);

/**
 * @brief Displays an error message without terminating the program.
 * Used for non-fatal errors or when you need to continue execution.
 * 
 * @param str Error message to display
 */
void	ft_error2(char *str);

/**
 * @brief Prints RGB color values for debugging.
 * Displays floor and ceiling RGB values from parser structure.
 * 
 * @param game Pointer to game structure
 */
void	ft_printrgb(t_game *game);

/**
 * @brief Prints all game data for debugging purposes.
 * Displays map, parser data, and other relevant information.
 * 
 * @param game Pointer to game structure
 */
void	print_all(t_game *game);

#endif