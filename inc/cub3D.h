/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 09:40:40 by ogoman            #+#    #+#             */
/*   Updated: 2024/09/10 08:57:49 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include "game_mlx.h"
# include "keycodes.h"
# include "ray_cast.h"
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

/* Перечисление для обработки различных сообщений об ошибках */
typedef enum e_cub_err
{
	ERR_END,           // Конец программы
	ERR_INV_AC,        // Неверный доступ
	ERR_INV_EXT,       // Неверное расширение файла
	ERR_INV_FILE,      // Неверный файл
	ERR_EMPTY_FILE,    // Пустой файл
	ERR_OUT_OF_MEMORY, // Нет памяти
	ERR_INV_COLOR,     // Неверный цвет
	ERR_INV_WALL,      // Неверная стена
	ERR_INV_MAP,       // Неверная карта
	ERR_INV_CHARAC,    // Неверный символ
	ERR_INV_PLAYER,    // Неверный игрок
	ERR_INV_TEX,       // Неверная текстура
	ERR_INV_PATH       // Неверный путь
}					t_cub_err;

/* Структура для хранения цветов с прозрачностью */
typedef struct s_color
{
	long alpha; // Прозрачность
	long red;   // Красный цвет
	long green; // Зеленый цвет
	long blue;  // Синий цвет
}					t_color;

// drawing structs
typedef struct s_point
{
	int				x;
	int				y;
	int				color;
}					t_point;

typedef struct s_bresenham
{
	int				dx;
	int				sx;
	int				dy;
	int				sy;
	int				err;
}					t_bresenham;

/* Структура для хранения текстур стен, пола и потолка */
typedef struct s_tex
{
	t_list *n_bak; //Буферные списки текстур для сторон света
	t_list *s_bak; //Буферные списки текстур для сторон света
	t_list *w_bak; //Буферные списки текстур для сторон света
	t_list *e_bak; //Буферные списки текстур для сторон света
	t_list *n;     // Список текстур для северной стены
	t_list *s;     // Список текстур для южной стены
	t_list *w;     // Список текстур для западной стены
	t_list *e;     // Список текстур для восточной стены
	t_img *b;      // Текстура для пола или потолка
	int floor;     // Цвет пола в формате RGB (например, 0xRRGGBB)
	int ceiling;   // Цвет потолка в формате RGB

	// Новые поля для текстур дверей
	t_img *door_closed; // Текстура для закрытой двери
	t_img *door_open;   // Текстура для открытой двери
}					t_tex;

/* Структура для хранения состояний клавиш */
typedef struct s_key
{
	int w_pressed;     // Клавиша W нажата
	int a_pressed;     // Клавиша A нажата
	int s_pressed;     // Клавиша S нажата
	int d_pressed;     // Клавиша D нажата
	int left_pressed;  // Клавиша влево нажата
	int right_pressed; // Клавиша вправо нажата
}					t_key;

/* Структура для хранения атрибутов игрока */
typedef struct s_player
{
	float position_x;  // Позиция игрока по оси X
	float position_y;  // Позиция игрока по оси Y
	char dir;          // Направление игрока (N, S, E, W)
	float speed;       // Скорость игрока
	int door_cooldown; // Взаимодействие с дверями
	t_key keys;        // Состояние клавиш игрока

	// Новые поля для Ray-Casting
	float dir_x;   // Направление взгляда по оси X
	float dir_y;   // Направление взгляда по оси Y
	float plane_x; // Плоскость камеры по оси X
	float plane_y; // Плоскость камеры по оси Y
}					t_player;

typedef struct s_ray
{
	float	angle_increment; // Угол между лучами
	float	current_angle;   // Текущий угол луча
	float	cos;             // Косинус угла луча
	float	sin;             // Синус угла луча
	float	hfov;            // Горизонтальное поле зрения
	float	max_distance;    // Предел расстояния для лучей
	int		precision;         // Точность расчета лучей
}			t_ray;

typedef struct s_ray_data
{
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		side;
	double	perp_wall_dist;
}			t_ray_data;


/* Структура для хранения состояния игры */
typedef struct s_game
{
	int fd;            // Дескриптор файла карты
	char **map;        // Двумерный массив карты
	int height;        // Высота карты
	int width;         // Ширина карты
	int rate;          // Частота обновления
	long frame_count;  // Количество кадров
	void *mlx_ptr;     // Указатель на MiniLibX
	void *win_ptr;     // Указатель на окно
	t_img win_img;     // Изображение окна
	t_img minimap;     // Миникарта
	t_img miniview;    // Мини-вид
	int minimap_scale; // Масштаб одного элемента карты в пикселях
	t_img			win_g;
	t_img			win_r;
	long nframes; //Количество кадров
	t_img *scope; // Целевой прицел
	t_tex tex;    // Текстуры для игры
	t_ray ray;    // Данные для лучей
	t_player pl;  // Игрок
	float x;      // Координата X (не используется в коде)
	float y;      // Координата Y (не используется в коде)
	
}					t_game;

typedef struct s_draw_params
{
	int draw_start;  // Начальная координата
	int draw_end;    // Конечная координата
	float wall_x;    // Точное положение попадания луча в стену.
	int line_height; // Высота линии на экране.
}					t_draw_params;

typedef struct s_move_data
{
	double			new_x;
	double			new_y;
}					t_move_data;

typedef struct s_texture_params
{
	t_img			*texture;
	t_draw_params	*params;
	t_ray_data		*ray;
}					t_texture_params;

typedef struct s_wall_params
{
	t_draw_params	params;
	t_img			*texture;
	float			wall_x;
}					t_wall_params;

// colors.c
/*Converts t_color components to ARGB integer value.*/
int					argb_from_color(t_color color);

/*Extracts ARGB components from an integer value into t_color structure.*/
t_color				color_from_argb(int color_value);

/* Drecreases RGB value of color as object gets further */
int					get_dist_color(int color, float ds, int tr);

/* Inverts color of window-sized image */
void				cub_invert_color(t_game *g);

/* Fills color int for floor and ceiling */
void				get_cf_color(char **dir, t_game *g);

// end.c
/*Frees allocated memory for animations starting from `start`.*/
void				free_animation(t_game *g, t_list *start);

/*Frees and destroys all images used in the game.*/
void				destroy_images(t_game *g);

/*Performs cleanup and frees all resources associated with the game.*/
void				cleanup_game(t_game *g);

// errors.c
/* Prints appropriate error message and exits, freeing everything */
int					handle_error(t_cub_err err, t_game *g, char *param, int c);

/* Prints usage for the cub3D program */
void				show_usage(int errno);

/* Function called by mlx when exiting */
int					cub_exit(void *param);

// setup_game.c

/*Initializes attributes and settings for the game.*/
void				init_attr(t_game *g);
/* Initializes game */
void				setup_game(t_game *g);
/*door action*/
void				action_door(t_game *g);

void				update_anim(t_game *g);
t_game				cub_init(void);
void				init_game(t_game *g, char *filename);

// key_events.c
/*Handles the event when a key is released.*/
int					cub_keyup(int k, t_game *g);
/*Handles the event when a key is pressed.*/
int					cub_keydown(int k, t_game *g);

// main.c
int					main(int ac, char **av);

// map_checking.c
/* Check every element of the map: spaces + characters */
void				check_elements(t_game *g);

/* Adds spaces to end of all lines to ensure all lines have the same width */
char				**alight_map_rows(t_game *g);

/*Checks for valid characters in the map and assigns player information.*/
void				check_characters(t_game *g, char **map, int i, int j);

/*Checks the adjacent cells around the current position in the map for '0' characters.*/
void				check_walls(t_game *g, char **map, int i, int j);

// map.c
/*Adds an image to the animation list and manages image count.*/
t_list				*get_anim(t_img *img, t_list **anim, int (*n)[2]);

/*Processes texture definitions and assigns them to the game structure.*/
void				check_textures(char *trim, t_game *g, int (*n)[2]);

/* Reads file with gnl */
void				read_map(char *file, t_game *g);

void process_line(char *line, t_game *g, int (*n)[2], int *texture_limit);

void initialize_map(char *file, t_game *g);

void load_side_textures(char **dir, t_game *g, int (*n)[2]);

/* Check possible map errors */
void				check_map(t_game *g);

// utils.c
/* Atoi for colors (more restrictive than original) */
int					parse_color_value(const char *nptr, long *value);

// update_cub.c
/*Updates the game state and redraws elements on the window.*/
int					cub_update(void *param);

/*Redraws an image element onto the game window at specified coordinates.*/
void				redraw_elem(t_game *g, t_img img, int x, int y);
void				clear_image(t_img *img, int color);

// ray_cast.c
/*Initializes raycasting parameters based on the player's direction.*/

void				cast_rays(t_game *g);


void				rotate_player(t_game *g);
void				move_player(t_game *g);

void				draw_background(t_game *g);

//ray_init.c
void				init_ray(t_game *g);

//ray_update.c
void	perform_dda(t_game *g, t_ray_data *ray, double delta_x,
		double delta_y);

// tew_test
void				draw_texture_line(t_game *g, int x, t_img *texture,
						t_draw_params *params, t_ray_data *ray);
void				draw_wall_line(t_game *g, int x, t_ray_data *ray);

// move
int					mouse_move(int x, int y, t_game *g);

// /* Checks player surroundings to open/close doors */
// void	action_door(t_game *g);

// minimap.c
void				draw_minimap(t_game *g);

// validations.c
void				validate_textures(t_game *g);
void				validate_colors(t_game *g);
void				check_file(int ac, char **av);

// sprites.c
/*Initializes the pointers to various sprite images and loads texture images.*/
void				init_sprites(t_game *g);

// doors.c
void				action_door(t_game *g);

// player_movement.c
void	set_player_direction(t_player *pl, char dir);

#endif
