
#include "../inc/cub3D.h"

void action_door(t_game *g)
{
    int door_x;
    int door_y;

    // Определяем координаты клетки перед игроком
    door_x = (int)(g->pl.position_x + g->pl.dir_x);
    door_y = (int)(g->pl.position_y + g->pl.dir_y);

    // Проверяем, находится ли перед игроком дверь и находимся ли мы в пределах карты
    if (door_x >= 0 && door_x < g->width && door_y >= 0 && door_y < g->height)
    {
        if (g->map[door_y][door_x] == 'D')  // Закрытая дверь
        {
            g->map[door_y][door_x] = 'O';  // Открываем дверь
            printf("Door opened at (%d, %d)\n", door_x, door_y);
        }
        else if (g->map[door_y][door_x] == 'O')  // Открытая дверь
        {
            g->map[door_y][door_x] = 'D';  // Закрываем дверь
            printf("Door closed at (%d, %d)\n", door_x, door_y);
        }
    }
}
