/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbenin <aarbenin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 09:40:40 by ogoman            #+#    #+#             */
/*   Updated: 2024/09/16 10:57:33 by aarbenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include "game_mlx.h"
# include "keycodes.h"
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

# define WIN_H 600
# define WIN_W 800
# define SIZE 7

# define M_PI 3.14159265358979323846
# define M_PI_2 1.57079632679489661923

/**
 * @brief Structure for drawing parameters.
 * 
 * This structure contains parameters used for drawing on the screen including
 * start and end coordinates of the drawing, the wall position, and the line
 * height.
 * typedef struct s_draw_params
{
	int draw_start;  // Start coordinate for drawing
	int draw_end;    // End coordinate for drawing
	float wall_x;    // Exact position of ray hitting the wall
	int line_height; // Height of the line on the screen
}					t_draw_params;
 */
typedef struct s_draw_params
{
	int				draw_start;
	int				draw_end;
	int				line_height;
	float			wall_x;
}					t_draw_params;

/**
 * @brief Structure for storing raycasting data.
 * 
 * This structure contains detailed data for a single
 * ray including its direction,
 * map coordinates, side distances, and step values.
 * typedef struct s_ray_data
{
	double	ray_dir_x;       // X direction of the ray
	double	ray_dir_y;       // Y direction of the ray
	int		map_x;           // X coordinate in the map
	int		map_y;           // Y coordinate in the map
	double	side_dist_x;    // Distance to the next x-side
	double	side_dist_y;    // Distance to the next y-side
	int		step_x;          // Step in the x direction
	int		step_y;          // Step in the y direction
	int		side;            // Side of the wall hit
	double	perp_wall_dist; // Perpendicular distance to the wall
}			t_ray_data;
 */
typedef struct s_ray_data
{
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	int				step_x;
	int				step_y;
	int				side;
	double			perp_wall_dist;
}			t_ray_data;

/**
 * @brief Enumeration for various error types in the program.
 * typedef enum e_cub_err
 * This enumeration defines different error codes that can be used
 * throughout
 * the program to represent various types of errors.
{
	ERR_END,           // End of the program
	ERR_INV_AC,        // Invalid access
	ERR_INV_EXT,       // Invalid file extension
	ERR_INV_FILE,      // Invalid file
	ERR_EMPTY_FILE,    // Empty file
	ERR_OUT_OF_MEMORY, // Out of memory
	ERR_INV_COLOR,     // Invalid color
	ERR_INV_WALL,      // Invalid wall
	ERR_INV_MAP,       // Invalid map
	ERR_INV_CHARAC,    // Invalid character
	ERR_INV_PLAYER,    // Invalid player
	ERR_INV_TEX,       // Invalid texture
	ERR_INV_PATH       // Invalid path
}					t_cub_err;
 */
typedef enum e_cub_err
{
	ERR_END,
	ERR_INV_AC,
	ERR_INV_EXT,
	ERR_INV_FILE,
	ERR_EMPTY_FILE,
	ERR_OUT_OF_MEMORY,
	ERR_INV_COLOR,
	ERR_INV_WALL,
	ERR_INV_MAP,
	ERR_INV_CHARAC,
	ERR_INV_PLAYER,
	ERR_INV_TEX,
	ERR_INV_PATH
}					t_cub_err;

typedef struct s_additional
{
	t_img				*texture;
	t_draw_params		*params;
	t_ray_data			*ray;
}				t_additional;

/**
 * @brief Structure for storing color with transparency.
 * 
 * This structure represents a color with its alpha (transparency), red,
 * green,
 * and blue components. Each component is represented as a long integer.
 * typedef struct s_color
{
	long alpha; // Transparency
	long red;   // Red color component
	long green; // Green color component
	long blue;  // Blue color component
}					t_color;
 */
typedef struct s_color
{
	long			alpha;
	long			red;
	long			green;
	long			blue;
}				t_color;

/**
 * @brief Structure for a 2D point.
 * 
 * This structure represents a point in 2D space with x and y coordinates
 * and a color value.
 * typedef struct s_point
{
	int				x;      // X coordinate
	int				y;      // Y coordinate
	int				color;  // Color value at the point
}					t_point;
 */
typedef struct s_point
{
	int				x;
	int				y;
	int				color;
}					t_point;

/**
 * @brief Structure for Bresenham's line algorithm parameters.
 * 
 * This structure contains parameters for Bresenham's line drawing algorithm,
 * which is used to draw lines on a grid.
 * typedef struct s_bresenham
{
	int				dx;     // Difference in x direction
	int				sx;     // Step in x direction
	int				dy;     // Difference in y direction
	int				sy;     // Step in y direction
	int				err;    // Error term for the algorithm
}					t_bresenham;
 */
typedef struct s_bresenham
{
	int				dx;
	int				sx;
	int				dy;
	int				sy;
	int				err;
}					t_bresenham;

/**
 * @brief Structure for storing textures for walls, floor, and ceiling.
 * 
 * This structure holds textures for the walls (north, south, west, east),
 * floor, ceiling, and additional textures for doors. It also contains
 * color values for floor and ceiling.
 * typedef struct s_tex
{
	t_list *n_bak; // Buffer list for north wall texture
	t_list *s_bak; // Buffer list for south wall texture
	t_list *w_bak; // Buffer list for west wall texture
	t_list *e_bak; // Buffer list for east wall texture
	t_list *n;     // List of textures for north wall
	t_list *s;     // List of textures for south wall
	t_list *w;     // List of textures for west wall
	t_list *e;     // List of textures for east wall
	t_img *b;      // Texture for floor or ceiling
	int floor;     // Floor color in RGB format (e.g., 0xRRGGBB)
	int ceiling;   // Ceiling color in RGB format

	// Additional fields for door textures
	t_img *door_closed; // Texture for a closed door
	t_img *door_open;   // Texture for an open door
}					t_tex;
 */
typedef struct s_tex
{
	int				floor;
	int				ceiling;
	t_list			*n_bak;
	t_list			*s_bak;
	t_list			*w_bak;
	t_list			*e_bak;
	t_list			*n;
	t_list			*s;
	t_list			*w;
	t_list			*e;
	t_img			*b;
	t_img			*door_closed;
	t_img			*door_open;
}					t_tex;

/**
 * @brief Structure for storing the states of player control keys.
 * 
 * This structure tracks the state (pressed or not) of the keys
 * used for player movement
 * and rotation.
 * typedef struct s_key
{
	int w_pressed;     // W key pressed
	int a_pressed;     // A key pressed
	int s_pressed;     // S key pressed
	int d_pressed;     // D key pressed
	int left_pressed;  // Left arrow key pressed
	int right_pressed; // Right arrow key pressed
}					t_key;
 */
typedef struct s_key
{
	int				w_pressed;
	int				a_pressed;
	int				s_pressed;
	int				d_pressed;
	int				left_pressed;
	int				right_pressed;
}					t_key;

/**
 * @brief Structure for storing player information.
 * 
 * This structure contains the player's position, direction,
 * speed, and key states.
 * It also includes additional fields for ray-casting.
 * typedef struct s_player
{
	float   position_x;  // Player's position along the X axis
	float   position_y;  // Player's position along the Y axis
	char    dir;          // Player's direction (N, S, E, W)
	float   speed;       // Player's speed
	t_key   keys;        // Player's key states

	// Additional fields for ray-casting
	float   dir_x;   // Direction of view along the X axis
	float   dir_y;   // Direction of view along the Y axis
	float   plane_x; // Camera plane along the X axis
	float   plane_y; // Camera plane along the Y axis
}			t_player;
 */
typedef struct s_player
{
	t_key			keys;
	float			position_x;
	float			position_y;
	char			dir;
	float			speed;
	float			dir_x;
	float			dir_y;
	float			plane_x;
	float			plane_y;
}			t_player;

/**
 * @brief Structure for storing ray parameters.
 * 
 * This structure holds parameters for ray casting including angle increment,
 * current angle, cosine and sine of the angle, horizontal field of view, 
 * maximum distance for rays, and precision of ray calculations.
 * typedef struct s_ray
{
	float	angle_increment; // Angle between rays
	float	current_angle;   // Current angle of the ray
	float	cos;             // Cosine of the ray angle
	float	sin;             // Sine of the ray angle
	float	hfov;            // Horizontal field of view
	float	max_distance;    // Maximum distance for rays
	int		precision;       // Precision of ray calculations
}			t_ray;
 */
typedef struct s_ray
{
	float			angle_increment;
	float			current_angle;
	float			cos;
	float			sin;
	float			hfov;
	float			max_distance;
	int				precision;
}			t_ray;

/**
 * @brief Structure for storing the game state.
 * 
 * This structure holds all necessary data for the game including map
 * information,
 * textures, player state, and various game parameters. It also manages
 * the window
 * and image data for rendering.
 * typedef struct s_game
{
	int fd;            // File descriptor for the map file
	char **map;        // 2D array representing the map
	int height;        // Height of the map
	int width;         // Width of the map
	int rate;          // Update rate
	long frame_count;  // Frame count
	void *mlx_ptr;     // Pointer to MiniLibX
	void *win_ptr;     // Pointer to the window
	t_img win_img;     // Window image
	t_img minimap;     // Minimap image
	t_img miniview;    // Mini-view image
	int minimap_scale; // Scale of a single map element in pixels
	t_img win_g;       // Additional image for game (e.g., game graphics)
	t_img win_r;       // Additional image for game (e.g., rendering)
	long nframes;      // Number of frames
	t_img *scope;      // Target scope image
	t_tex tex;         // Textures for the game
	t_ray ray;         // Ray data
	t_player pl;       // Player information
	t_img *welcome_screen; // Welcome screen image
	t_img scaled_welcome; // Scaled welcome screen image
	int is_paused;     // Pause flag (0 - game running, 1 - game paused)
	int was_paused;    // Flag to track if game was previously paused
	int window_width;  // Window width
	int window_height; // Window height
}					t_game;
 */
typedef struct s_game
{
	t_additional	additional;
	t_img			win_img;
	t_img			minimap;
	t_img			miniview;
	t_img			win_g;
	t_img			win_r;
	t_img			*scope;
	t_img			*welcome_screen;
	t_img			scaled_welcome;
	t_tex			tex;
	t_ray			ray;
	t_player		pl;
	int				fd;
	int				height;
	int				width;
	int				rate;
	int				minimap_scale;
	int				is_paused;
	int				was_paused;
	int				window_width;
	int				window_height;
	char			**map;
	long			nframes;
	long			frame_count;
	void			*mlx_ptr;
	void			*win_ptr;
}					t_game;

/**
 * @brief Structure for storing movement data.
 * 
 * This structure holds the new X and Y positions calculated for player movement.
 * typedef struct s_move_data
{
	double new_x; // New X position
	double new_y; // New Y position
}					t_move_data;
 */
typedef struct s_move_data
{
	double			new_x;
	double			new_y;
}					t_move_data;

/**
 * @brief Structure for texture drawing parameters.
 * 
 * This structure contains parameters needed for drawing textures including
 * the texture image, drawing parameters, and ray data.
 * typedef struct s_texture_params
{
	t_img *texture;    // Texture image to be used
	t_draw_params *params; // Parameters for drawing the texture
	t_ray_data *ray;   // Ray data related to the texture
}					t_texture_params;
 */
typedef struct s_texture_params
{
	t_img			*texture;
	t_draw_params	*params;
	t_ray_data		*ray;
}					t_texture_params;

/**
 * @brief Structure for wall rendering parameters.
 * typedef struct s_wall_params
{
	t_draw_params	params;     // Drawing parameters for the wall
	t_img			*texture;  // Pointer to the wall texture image
	float			wall_x;    // Exact position of the ray hit on the wall
}					t_wall_params;
 */
typedef struct s_wall_params
{
	t_draw_params	params;
	t_img			*texture;
	float			wall_x;
}					t_wall_params;

/**
 * @brief Structure for scaling parameters.
 * typedef struct s_scale_params
{
	int		scaled_width;  // Width of the scaled image
	int		scaled_height; // Height of the scaled image
	double	ratio;         // Scaling ratio
	int		x_offset;      // X offset for positioning
	int		y_offset;      // Y offset for positioning
}					t_scale_params;
 */
typedef struct s_scale_params
{
	int				scaled_width;
	int				scaled_height;
	double			ratio;
	int				x_offset;
	int				y_offset;
}					t_scale_params;

/**
 * @brief Structure for window parameters.
 * typedef struct s_window_params
{
	int		window_width;   // Width of the game window
	int		window_height;  // Height of the game window
	int		background_color; // Background color of the window (RGB format)
}					t_window_params;
 */
typedef struct s_window_params
{
	int				window_width;
	int				window_height;
	int				background_color;
}					t_window_params;

typedef struct s_minimap_params
{
	int				width;
	int				height;
	int				color;
	int				size;
}					t_minimap_params;

typedef struct s_rect_params
{
	t_vector		position;
	t_vector		dimensions;
	int				color;
}					t_rect_params;

typedef struct s_fov_params
{
	int				fov_length;
	int				fov_angle;
	int				minimap_scale;
	int				player_size;
	int				center_x;
	int				center_y;
	int				color;
	double			angle_start;
	double			angle_end;
}					t_fov_params;

// *****************************************************************************
// *                              animation.c                                  *
// *****************************************************************************
void				update_anim(t_game *g);

// *****************************************************************************
// *                                  color.c                                  *
// *****************************************************************************
int					argb_from_color(t_color color);
t_color				color_from_argb(int color_value);
int					get_dist_color(int color, float ds, int tr);
void				cub_invert_color(t_game *g);
void				get_cf_color(char **dir, t_game *g);

// *****************************************************************************
// *                               color_utils.c                               *
// *****************************************************************************
int					blend_colors(int color1, int color2, float alpha);
int					parse_color_value(const char *nptr, long *value);

// *****************************************************************************
// *                                doors.c                                    *
// *****************************************************************************
void				action_door(t_game *g);

// *****************************************************************************
// *                               drawing_utils.c                             *
// *****************************************************************************
void				mlx_draw_line(t_img *img, t_point start, t_point end);
void				clear_image(t_img *img, int color);

// *****************************************************************************
// *                                   end.c                                   *
// *****************************************************************************
void				free_animation(t_game *g, t_list *start);
void				destroy_images(t_game *g);
void				cleanup_game(t_game *g);

// *****************************************************************************
// *                                 errors.c                                  *
// *****************************************************************************
int					handle_error(t_cub_err err, t_game *g, char *param, int c);
void				show_usage(int errno);
int					cub_exit(void *param);

// *****************************************************************************
// *                              image_utils.c                                *
// *****************************************************************************
t_img				*load_img(void *mlx_ptr, char *file_path);
int					load_image_from_file(void *mlx_ptr, char *file_path,
						t_img *image);
t_img				*create_image_structure(void);
int					is_valid_image_path(const char *file_path);

// *****************************************************************************
// *                               init_game.c                                 *
// *****************************************************************************
void				init_attr(t_game *g);
t_game				cub_init(void);
void				init_game(t_game *g, char *filename);
void				init_minimap(t_game *g);
void				init_welcome_screen(t_game *g);

// *****************************************************************************
// *                                input.c                                    *
// *****************************************************************************
void				keyboard_input(t_game *g);
int					mouse_input(int x, int y, t_game *g);

// *****************************************************************************
// *                               key_events.c                                *
// *****************************************************************************
int					cub_keyup(int k, t_game *g);
int					cub_keydown(int k, t_game *g);

// *****************************************************************************
// *                                  main.c                                   *
// *****************************************************************************
int					main(int ac, char **av);

// *****************************************************************************
// *                                  map.c                                    *
// *****************************************************************************
void				check_textures(char *trim, t_game *g, int (*n)[2]);
void				read_map(char *file, t_game *g);
void				initialize_map(char *file, t_game *g);
void				check_map(t_game *g);

// *****************************************************************************
// *                              map_graphics.c                               *
// *****************************************************************************
t_list				*get_anim(t_img *img, t_list **anim, int (*n)[2]);
void				check_textures(char *trim, t_game *g, int (*n)[2]);

// *****************************************************************************
// *                             map_checking.c                                *
// *****************************************************************************
void				check_elements(t_game *g);
char				**alight_map_rows(t_game *g);
void				check_characters(t_game *g, char **map, int i, int j);
void				check_walls(t_game *g, char **map, int i, int j);

// *****************************************************************************
// *                               map_utils.c                                 *
// *****************************************************************************
void				handle_player_direction(t_game *g, char character, int i,
						int j);
void				check_invalid_character(char character, t_game *g);
char				**alight_map_rows(t_game *g);

// *****************************************************************************
// *                                minimap.c                                  *
// *****************************************************************************
void				draw_minimap(t_game *g);

// *****************************************************************************
// *                           minimap_border.c                                *
// *****************************************************************************
void				draw_minimap_border(t_game *g);

// *****************************************************************************
// *                            minimap_fov.c                                  *
// *****************************************************************************
void				draw_fov(t_game *g);

// *****************************************************************************
// *                             pause_screen.c                                *
// *****************************************************************************
void				display_pause_screen(t_game *g);

// *****************************************************************************
// *                           player_movement.c                               *
// *****************************************************************************
void				set_player_direction(t_player *pl, char dir);

// *****************************************************************************
// *                            player_rotate.c                                *
// *****************************************************************************
void				rotate_player(t_game *g);
void				rotate_left(t_player *pl, double rotation_speed);
void				rotate_right(t_player *pl, double rotation_speed);

// *****************************************************************************
// *                               ray_cast.c                                  *
// *****************************************************************************
void				cast_rays(t_game *g);
void				rotate_player(t_game *g);
void				move_player(t_game *g);
void				draw_background(t_game *g);

// *****************************************************************************
// *                               ray_init.c                                  *
// *****************************************************************************
void				init_ray(t_game *g);

// *****************************************************************************
// *                              ray_update.c                                 *
// *****************************************************************************
void				perform_dda(t_game *g, t_ray_data *ray, double delta_x,
						double delta_y);

// *****************************************************************************
// *                             setup_game.c                                  *
// *****************************************************************************
void				setup_game(t_game *g);

// *****************************************************************************
// *                                sprites.c                                  *
// *****************************************************************************
void				init_sprites(t_game *g);

// *****************************************************************************
// *                               tew_test.c                                  *
// *****************************************************************************
void				draw_texture_line(t_game *g, int x);
void				draw_wall_line(t_game *g, int x, t_ray_data *ray);

// *****************************************************************************
// *                                 utils.c                                   *
// *****************************************************************************
int					parse_color_value(const char *nptr, long *value);

// *****************************************************************************
// *                             update_cub.c                                  *
// *****************************************************************************
void				redraw_elem(t_game *g, t_img img, int x, int y);
void				update_anim(t_game *g);
int					update_cub(void *param);

// *****************************************************************************
// *                             validations.c                                 *
// *****************************************************************************
void				validate_textures(t_game *g);
void				validate_colors(t_game *g);
void				check_file(int ac, char **av);

#endif
