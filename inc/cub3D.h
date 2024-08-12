/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 09:40:40 by ogoman            #+#    #+#             */
/*   Updated: 2024/08/12 06:40:33 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

# include "../libft/libft.h"
# include "keycodes.h"
# include <mlx.h>
# include "../get_next_line/get_next_line.h"
# include "game_mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# ifndef WIN_H
#  define WIN_H 480
# endif

# ifndef WIN_W
#  define WIN_W 640
# endif

# ifndef SIZE
#  define SIZE 7
# endif

/* Перечисление для обработки различных сообщений об ошибках */
typedef enum e_cub_err
{
    ERR_END,          // Конец программы
    ERR_INV_AC,       // Неверный доступ
    ERR_INV_EXT,      // Неверное расширение файла
    ERR_INV_FILE,     // Неверный файл
    ERR_EMPTY_FILE,   // Пустой файл
    ERR_OUT_OF_MEMORY,    // Нет памяти
    ERR_INV_COLOR,    // Неверный цвет
    ERR_INV_WALL,     // Неверная стена
    ERR_INV_MAP,      // Неверная карта
    ERR_INV_CHARAC,   // Неверный символ
    ERR_INV_PLAYER,   // Неверный игрок
    ERR_INV_TEX,      // Неверная текстура
    ERR_INV_PATH       // Неверный путь
} t_cub_err;

/* Структура для хранения цветов с прозрачностью */
typedef struct s_color
{
    long alpha; // Прозрачность
    long red; // Красный цвет
    long green; // Зеленый цвет
    long blue; // Синий цвет
} t_color;

/* Структура для хранения текстур стен, пола и потолка */
typedef struct s_tex
{
    t_list *n;       // Список текстур для северной стены
    t_list *s;       // Список текстур для южной стены
    t_list *w;       // Список текстур для западной стены
    t_list *e;       // Список текстур для восточной стены
    t_img *b;        // Текстура для пола или потолка
    int floor;       // Цвет пола в формате RGB (например, 0xRRGGBB)
    int ceiling;     // Цвет потолка в формате RGB
} t_tex;

/* Структура для хранения состояний клавиш */
typedef struct s_key
{
    int w_pressed;      // Клавиша W нажата
    int a_pressed;      // Клавиша A нажата
    int s_pressed;      // Клавиша S нажата
    int d_pressed;      // Клавиша D нажата
    int left_pressed;   // Клавиша влево нажата
    int right_pressed;  // Клавиша вправо нажата
} t_key;

/* Структура для хранения атрибутов игрока */
typedef struct s_player
{
    float position_x;    // Позиция игрока по оси X
    float position_y;    // Позиция игрока по оси Y
    char dir;           // Направление игрока
    float speed;        // Скорость игрока
    int door_cooldown;  // взаимодействия с дверями
    t_key keys;         // Состояние клавиш игрока
} t_player;

/* Структура для хранения состояния игры */
typedef struct s_text_game
{
    int fd;             // Дескриптор файла карты
    char **map;         // Двумерный массив карты
    int height;        // Высота карты
    int width;         // Ширина карты
    int rate;          // Частота обновления
    long frame_count;      // Количество кадров
    void *mlx_ptr;     // Указатель на MiniLibX
    void *win_ptr;     // Указатель на окно
    t_img win_img;     // Изображение окна
    t_img minimap;     // Миникарта
    t_img miniview;    // Мини-вид
    t_img *scope;      // Целевой прицел
    t_tex tex;         // Текстуры для игры
    t_player pl;       // Игрок
    float x;           // Координата X (не используется в коде)
    float y;           // Координата Y (не используется в коде)
} t_text_game;



// colors.c
/*Converts t_color components to ARGB integer value.*/
int argb_from_color(t_color color);

/*Extracts ARGB components from an integer value into t_color structure.*/
t_color color_from_argb(int color_value);

/* Drecreases RGB value of color as object gets further */
int		get_dist_color(int color, float ds, int tr);

/* Inverts color of window-sized image */
void	cub_invert_color(t_text_game *g);

/* Fills color int for floor and ceiling */
void	get_cf_color(char **dir, t_text_game *g);



// end.c
/*Frees allocated memory for animations starting from `start`.*/
void	free_animation(t_text_game *g, t_list *start);

/*Frees and destroys all images used in the game.*/
void	destroy_images(t_text_game *g);

/*Performs cleanup and frees all resources associated with the game.*/
void	cleanup_game(t_text_game *g);



// errors.c
/* Prints appropriate error message and exits, freeing everything */
int		handle_error(t_cub_err err, t_text_game *g, char *param, int c);

/* Prints usage for the cub3D program */
void	show_usage(int errno);

/* Function called by mlx when exiting */
int		cub_exit(void *param);



// game_init.c
/*Handles the event when a key is released.*/
int cub_keyup(int k, t_text_game *g);

/*Handles the event when a key is pressed.*/
int cub_keydown(int k, t_text_game *g);

/*Initializes attributes and settings for the game.*/
void init_attr(t_text_game *g);

/* Initializes game */
void	game_init(t_text_game *g);



// main.c
/*Initializes the pointers to various sprite images and loads texture images.*/
void	init_sprites(t_text_game *g);

/*Main entry point of the program.*/
int		main(int ac, char **av);



// map_checking.c
/* Check every element of the map: spaces + characters */
void	check_elements(t_text_game *g);

/* Adds spaces to end of all lines to ensure all lines have the same width */
char	**alight_map_rows(t_text_game *g);

/*Checks for valid characters in the map and assigns player information.*/
void	check_characters(t_text_game *g, char **map, int i, int j);

/*Checks the adjacent cells around the current position in the map for '0' characters.*/
void check_walls(t_text_game *g, char **map, int i, int j);



// map.c
/*Adds an image to the animation list and manages image count.*/
t_list *get_anim(t_img *img, t_list **anim, int (*n)[2]);

/*Processes texture definitions and assigns them to the game structure.*/
void	check_textures(char *trim, t_text_game *g, int (*n)[2]);

/* Reads file with gnl */
void	read_map(char *file, t_text_game *g);

/* Check possible map errors */
void	check_map(t_text_game *g);



// utils.c
/* Atoi for colors (more restrictive than original) */
int		parse_color_value(const char *nptr, long *value);



// /* Checks player surroundings to open/close doors */
// void	action_door(t_text_game *g);

#endif
