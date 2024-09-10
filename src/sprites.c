#include "../inc/cub3D.h"



/**
 * Initializes the pointers to various sprite images and loads texture images.
 * 
 * Sets all sprite pointers to NULL initially to avoid accessing uninitialized pointers.
 * Loads images for different textures and ensures they are successfully loaded, reporting 
 * an error if any texture fails to load.
 * 
 * @param g Pointer to the game structure where sprite and texture information is stored.
 */
void init_sprites(t_game *g)
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

    // Функция load_img загружает изображения из файлов и возвращает указатели на них.
    g->tex.b = load_img(g->mlx_ptr, "textures/black.xpm"); // Загрузка текстуры черного цвета
    g->scope = load_img(g->mlx_ptr, "textures/saw.xpm"); // Загрузка текстуры прицела

    // Проверка успешности загрузки текстур.
    if (!g->tex.b || !g->tex.b->i || !g->scope || !g->scope->i)
        handle_error(ERR_INV_PATH, g, NULL, 1); // Обработка ошибки загрузки текстур
}
