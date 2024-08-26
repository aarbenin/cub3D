#include "../inc/cub3D.h"

void move_player(t_text_game *g)
{
    double move_speed = g->pl.speed;
    double new_x = g->pl.position_x;
    double new_y = g->pl.position_y;

    if (g->pl.keys.a_pressed) //d
    {
        new_x += g->pl.dir_x * move_speed;
        new_y += g->pl.dir_y * move_speed;
    }
    if (g->pl.keys.d_pressed)
    {
        new_x -= g->pl.dir_x * move_speed;
        new_y -= g->pl.dir_y * move_speed;
    }
    if (g->pl.keys.s_pressed) //s
    {
        new_x -= g->pl.plane_x * move_speed;
        new_y -= g->pl.plane_y * move_speed;
    }
    if (g->pl.keys.w_pressed) //w
    {
        new_x += g->pl.plane_x * move_speed;
        new_y += g->pl.plane_y * move_speed;
    }
    if (g->map[(int)new_y][(int)new_x] != '1')
    {
        g->pl.position_x = new_x;
        g->pl.position_y = new_y;
    }
    printf("New position: x = %f, y = %f\n", g->pl.position_x, g->pl.position_y);
}



void rotate_player(t_text_game *g)
{
    double rotation_speed = 0.02;  // Скорость вращения
    double old_dir_x;
    double old_plane_x;

    if (g->pl.keys.left_pressed)
    {
        old_dir_x = g->pl.dir_x;
        g->pl.dir_x = g->pl.dir_x * cos(-rotation_speed) - g->pl.dir_y * sin(-rotation_speed);
        g->pl.dir_y = old_dir_x * sin(-rotation_speed) + g->pl.dir_y * cos(-rotation_speed);

        old_plane_x = g->pl.plane_x;
        g->pl.plane_x = g->pl.plane_x * cos(-rotation_speed) - g->pl.plane_y * sin(-rotation_speed);
        g->pl.plane_y = old_plane_x * sin(-rotation_speed) + g->pl.plane_y * cos(-rotation_speed);
    }
    if (g->pl.keys.right_pressed)
    {
        old_dir_x = g->pl.dir_x;
        g->pl.dir_x = g->pl.dir_x * cos(rotation_speed) - g->pl.dir_y * sin(rotation_speed);
        g->pl.dir_y = old_dir_x * sin(rotation_speed) + g->pl.dir_y * cos(rotation_speed);

        old_plane_x = g->pl.plane_x;
        g->pl.plane_x = g->pl.plane_x * cos(rotation_speed) - g->pl.plane_y * sin(rotation_speed);
        g->pl.plane_y = old_plane_x * sin(rotation_speed) + g->pl.plane_y * cos(rotation_speed);
    }
    printf("Rotated Direction: dir_x = %f, dir_y = %f\n", g->pl.dir_x, g->pl.dir_y);
    printf("Rotated Plane: plane_x = %f, plane_y = %f\n", g->pl.plane_x, g->pl.plane_y);
}
