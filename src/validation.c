#include "../inc/cub3D.h"

/**
 * Validates the presence of all required textures in the game structure.
 * 
 * Checks if all the necessary textures (north, south, east, west) are loaded and reports 
 * an error if any of the textures are missing.
 * 
 * @param g Pointer to the game structure containing texture information.
 */
// void validate_textures(t_game *g)
// {
//     handle_error(ERR_INV_TEX, g, NULL, 
//         !g->tex.n || !g->tex.s || !g->tex.e || !g->tex.w ||
//         !g->tex.door_closed || !g->tex.door_open);
// }
void validate_textures(t_game *g)
{
	handle_error(ERR_INV_TEX, g, NULL, 
		!g->tex.n || !g->tex.s || !g->tex.e || !g->tex.w);
}


/**
 * Validates the presence of floor and ceiling colors in the game structure.
 * 
 * Checks if the floor and ceiling colors are set in the game structure and reports an error 
 * if either color is missing.
 * 
 * @param g Pointer to the game structure containing color information.
 */
void validate_colors(t_game *g)
{
	handle_error(ERR_INV_COLOR, g, NULL, g->tex.floor == -1 || g->tex.ceiling == -1);
}


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
void check_file(int ac, char **av)
{
	int fd;

	handle_error(ERR_INV_AC, NULL, NULL, ac != 2); // esli ne ravno 2 vizivaetsja handle_error
	fd = open(av[1], O_RDONLY);
	close(fd);
	handle_error(ERR_INV_FILE, NULL, av[1], fd < 0);
	if (ft_strrncmp(".cub", av[1], 4))
		handle_error(ERR_INV_EXT, NULL, NULL, 1);
}
