/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:47:08 by ogoman            #+#    #+#             */
/*   Updated: 2024/08/27 10:32:17 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

// Прототипы функций
static void init_game(t_text_game *g, char *filename);
static void validate_textures(t_text_game *g);
static void validate_colors(t_text_game *g);


/**
 * Validates the command-line arguments and checks the file extension and existence.
 * 
 * Ensures that exactly one argument is provided (the map file) and that the file has a 
 * '.cub' extension. Checks if the file can be opened and reports errors if the file 
 * does not exist or has an incorrect extension.
 * 
 * @param ac The argument count from the command line.
 * @param av The argument vector (command line arguments).
 */
static void check_file(int ac, char **av)
{
	int fd;

	handle_error(ERR_INV_AC, NULL, NULL, ac != 2); // esli ne ravno 2 vizivaetsja handle_error
	fd = open(av[1], O_RDONLY);
	close(fd);
	handle_error(ERR_INV_FILE, NULL, av[1], fd < 0);
	if (ft_strrncmp(".cub", av[1], 4))
		handle_error(ERR_INV_EXT, NULL, NULL, 1);
}

/**
 * Initializes the pointers to various sprite images and loads texture images.
 * 
 * Sets all sprite pointers to NULL initially to avoid accessing uninitialized pointers.
 * Loads images for different textures and ensures they are successfully loaded, reporting 
 * an error if any texture fails to load.
 * 
 * @param g Pointer to the game structure where sprite and texture information is stored.
 */
void init_sprites(t_text_game *g)
{
    // Инициализация указателей на изображения и текстуры.
    // Указатели на изображения и текстуры устанавливаются в NULL, чтобы избежать доступа к неинициализированным указателям.
    g->win_img.i = NULL;    // Указатель на изображение окна
    g->minimap.i = NULL;    // Указатель на миникарту
    g->miniview.i = NULL;   // Указатель на минивид
	g->tex.n = NULL;
	g->tex.n_bak = NULL;
	g->tex.s = NULL;
	g->tex.s_bak = NULL;
	g->tex.e = NULL;
	g->tex.e_bak = NULL;
	g->tex.w = NULL;
	g->tex.w_bak = NULL;
    g->win_g.i = NULL;
    g->win_r.i = NULL;

    // Функция load_img загружает изображения из файлов и возвращает указатели на них.
    g->tex.b = load_img(g->mlx_ptr, "textures/black.xpm"); // Загрузка текстуры черного цвета
    g->scope = load_img(g->mlx_ptr, "textures/scope.xpm"); // Загрузка текстуры прицела

    // Проверка успешности загрузки текстур.
    if (!g->tex.b || !g->tex.b->i || !g->scope || !g->scope->i)
        handle_error(ERR_INV_PATH, g, NULL, 1); // Обработка ошибки загрузки текстур
}

/**
 * Initializes the game structure with default values.
 * 
 * Sets initial values for various game parameters, including window dimensions, file descriptor, 
 * frame count, player direction and position, and MLX pointers. Also initializes the sprites and 
 * clears player key structure.
 * 
 * @return An initialized `t_text_game` structure with default values.
 */
static t_text_game cub_init(void)
{
	t_text_game g;
    
    g.rate = 30;
    g.nframes = 0;
	g.width = 0;						 // Ширина окна, инициализируется нулём
	g.height = 0;						 // Высота окна, инициализируется нулём
	g.fd = -1;							 // Дескриптор файла, -1 означает, что файл ещё не открыт
	g.frame_count = 0;					 // Счетчик кадров, инициализируется нулём
	g.pl.dir = 0;						 // Направление игрока, инициализируется нулём
	g.map = NULL;						 // Указатель на карту, инициализируется NULL (пусто)
	g.mlx_ptr = NULL;					 // Указатель на MLX (MiniLibX), инициализируется NULL
	g.win_ptr = NULL;					 // Указатель на окно, инициализируется NULL
	g.mlx_ptr = mlx_init();				 // Инициализация MLX
	g.tex.floor = -1;					 // Цвет пола, -1 указывает на неинициализированное значение
	g.tex.ceiling = -1;					 // Цвет потолка, -1 указывает на неинициализированное значение
	g.pl.position_x = -1;				 // Позиция игрока по X, -1 означает, что позиция не задана
	g.pl.position_y = -1;				 // Позиция игрока по Y, -1 означает, что позиция не задана
	g.pl.speed = 0.10;					 // Скорость игрока, инициализирована значением 0.10
	g.pl.door_cooldown = 0;				 // Охлаждение двери, инициализируется нулём
	g.rate = 30;						 // Частота кадров или обновления, инициализируется значением 30
	init_sprites(&g);					 // Инициализация спрайтов
	ft_bzero(&g.pl.keys, sizeof(t_key)); // Обнуление структуры клавиш игрока
	return (g); // Возвращает инициализированную структуру игры
}

/**
 * Main entry point of the program.
 * 
 * Performs initial file checks, initializes the game, validates textures and colors, processes 
 * and checks the map, and starts the game. Ensures that all necessary game components are set up 
 * and verified before launching the game.
 * 
 * @param ac The argument count from the command line.
 * @param av The argument vector (command line arguments).
 * 
 * @return An integer representing the exit status of the program.
 */
int main(int ac, char **av)
{
    t_text_game g;

    // Проверка количества аргументов и расширения файла
    check_file(ac, av);

    // Инициализация игры
    init_game(&g, av[1]);

    // Проверка текстур и цветов
    validate_textures(&g);
    validate_colors(&g);

    // Преобразование карты и проверка карты
    char **updated_map = alight_map_rows(&g);
    ft_free_matrix(&g.map);
    g.map = updated_map;
    check_map(&g);

    // Инициализация игры и запуск
    game_init(&g);

    return (0);
}

/**
 * Initializes the game environment by setting up the game structure and reading the map.
 * 
 * Calls the `cub_init` function to initialize the game structure and then reads the map file 
 * specified by the filename argument. Sets up the game with the necessary map and texture data.
 * 
 * @param g Pointer to the game structure to be initialized.
 * @param filename The path to the map file.
 */
static void init_game(t_text_game *g, char *filename)
{
    *g = cub_init();
    read_map(filename, g);
}

/**
 * Validates the presence of all required textures in the game structure.
 * 
 * Checks if all the necessary textures (north, south, east, west) are loaded and reports 
 * an error if any of the textures are missing.
 * 
 * @param g Pointer to the game structure containing texture information.
 */
static void validate_textures(t_text_game *g)
{
    handle_error(ERR_INV_TEX, g, NULL, !g->tex.n || !g->tex.s || !g->tex.e || !g->tex.w);
}

/**
 * Validates the presence of floor and ceiling colors in the game structure.
 * 
 * Checks if the floor and ceiling colors are set in the game structure and reports an error 
 * if either color is missing.
 * 
 * @param g Pointer to the game structure containing color information.
 */
static void validate_colors(t_text_game *g)
{
    handle_error(ERR_INV_COLOR, g, NULL, g->tex.floor == -1 || g->tex.ceiling == -1);
}
