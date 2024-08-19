// #include "../inc/cub3D.h"

// void move_player(t_text_game *g)
// {
//     if (g->pl.keys.w_pressed)
//     {
//         g->pl.position_x += g->pl.dir_x * g->pl.speed;
//         g->pl.position_y += g->pl.dir_y * g->pl.speed;
//     }
//     if (g->pl.keys.s_pressed)
//     {
//         g->pl.position_x -= g->pl.dir_x * g->pl.speed;
//         g->pl.position_y -= g->pl.dir_y * g->pl.speed;
//     }
//     if (g->pl.keys.a_pressed)
//     {
//         g->pl.position_x -= g->pl.plane_x * g->pl.speed;
//         g->pl.position_y -= g->pl.plane_y * g->pl.speed;
//     }
//     if (g->pl.keys.d_pressed)
//     {
//         g->pl.position_x += g->pl.plane_x * g->pl.speed;
//         g->pl.position_y += g->pl.plane_y * g->pl.speed;
//     }
// }

// void rotate_player(t_text_game *g)
// {
//     double old_dir_x;
//     double old_plane_x;
//     double rotation_speed = g->pl.speed * 2;

//     if (g->pl.keys.left_pressed)
//     {
//         old_dir_x = g->pl.dir_x;
//         g->pl.dir_x = g->pl.dir_x * cos(-rotation_speed) - g->pl.dir_y * sin(-rotation_speed);
//         g->pl.dir_y = old_dir_x * sin(-rotation_speed) + g->pl.dir_y * cos(-rotation_speed);

//         old_plane_x = g->pl.plane_x;
//         g->pl.plane_x = g->pl.plane_x * cos(-rotation_speed) - g->pl.plane_y * sin(-rotation_speed);
//         g->pl.plane_y = old_plane_x * sin(-rotation_speed) + g->pl.plane_y * cos(-rotation_speed);
//     }
//     if (g->pl.keys.right_pressed)
//     {
//         old_dir_x = g->pl.dir_x;
//         g->pl.dir_x = g->pl.dir_x * cos(rotation_speed) - g->pl.dir_y * sin(rotation_speed);
//         g->pl.dir_y = old_dir_x * sin(rotation_speed) + g->pl.dir_y * cos(rotation_speed);

//         old_plane_x = g->pl.plane_x;
//         g->pl.plane_x = g->pl.plane_x * cos(rotation_speed) - g->pl.plane_y * sin(rotation_speed);
//         g->pl.plane_y = old_plane_x * sin(rotation_speed) + g->pl.plane_y * cos(rotation_speed);
//     }
// }
