#include "../inc/cub3D.h"

void draw_texture_line(t_text_game *g, int x, t_img *texture, t_draw_params *params, t_ray_data *ray);

// typedef struct s_draw_params
// {
//     int draw_start;    // Начальная координата 
//     int draw_end;      // Конечная координата 
//     float wall_x;      // Точное положение попадания луча в стену.
//     int line_height;   // Высота линии на экране.
// } t_draw_params;


void draw_texture_line(t_text_game *g, int x, t_img *texture, t_draw_params *params, t_ray_data *ray)
{
    int y;
    int tex_x;
    int tex_y;
    int color;
    float step;
    float tex_pos;

    // Определение координаты текстуры X
    tex_x = (int)(params->wall_x * (float)texture->width);
    if ((ray->side == 0 && ray->ray_dir_x > 0) || (ray->side == 1 && ray->ray_dir_y < 0))
        tex_x = texture->width - tex_x - 1;

    // Определение шага для текстуры и начальной позиции
    step = 1.0 * texture->height / params->line_height;
    tex_pos = (params->draw_start - WIN_H / 2 + params->line_height / 2) * step;

    // Использование while для отрисовки вертикальной линии с текстурой
    y = params->draw_start;
    while (y < params->draw_end)
    {
        // Вычисляем координаты Y для текстуры
        tex_y = (int)tex_pos & (texture->height - 1);
        tex_pos += step;

        // Получаем цвет пикселя из текстуры
        color = get_pixel_color(texture, tex_x, tex_y);

        // Затемнение для вертикальных стен (чтобы отличать стороны стены)
        if (ray->side == 1)
            color = (color >> 1) & 0x7F7F7F;

        // Устанавливаем пиксель на изображении
        put_pixel(&g->win_img, x, y, color);

        // Увеличиваем y для следующей итерации
        y++;
    }
}


void draw_wall_line(t_text_game *g, int x, t_ray_data *ray)
{
    t_draw_params params;
    t_img *texture;

    // Определение высоты линии
    params.line_height = (int)(WIN_H / ray->perp_wall_dist);

    // Определение границ рисования на экране
    params.draw_start = -params.line_height / 2 + WIN_H / 2;
    if (params.draw_start < 0)
        params.draw_start = 0;
    params.draw_end = params.line_height / 2 + WIN_H / 2;
    if (params.draw_end >= WIN_H)
        params.draw_end = WIN_H - 1;

    // Выбор текстуры на основе стороны попадания луча
    if (ray->side == 0)
    {
        if (ray->ray_dir_x > 0)
            texture = (t_img *)g->tex.e->content; // Восточная стена
        else
            texture = (t_img *)g->tex.w->content; // Западная стена
    }
    else
    {
        if (ray->ray_dir_y > 0)
            texture = (t_img *)g->tex.s->content; // Южная стена
        else
            texture = (t_img *)g->tex.n->content; // Северная стена
    }

    // Вычисление точной координаты пересечения стены в текстуре
    float wall_x;
    if (ray->side == 0)
        wall_x = g->pl.position_y + ray->perp_wall_dist * ray->ray_dir_y;
    else
        wall_x = g->pl.position_x + ray->perp_wall_dist * ray->ray_dir_x;
    
    wall_x -= floor(wall_x); // Убираем целую часть

    // Установка параметров рисования в структуре t_draw_params
    params.wall_x = wall_x;

    // Вызов функции рисования текстуры
    draw_texture_line(g, x, texture, &params, ray);
}


