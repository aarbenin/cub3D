/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 08:32:41 by ogoman            #+#    #+#             */
/*   Updated: 2024/08/12 06:35:47 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/**
 * Sets the color of a specific pixel at the given coordinates in the image.
 * 
 * @param img Pointer to the t_img structure representing the image.
 * @param x X-coordinate of the pixel to set.
 * @param y Y-coordinate of the pixel to set.
 * @param color Color to set the pixel to.
 */
void put_pixel(t_img *img, int x, int y, int color)
{
    char *pixel_location;

    pixel_location = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(unsigned int *)pixel_location = color;
}

/**
 * Retrieves the color of a specific pixel at the given coordinates in the image.
 * 
 * @param img Pointer to the t_img structure representing the image.
 * @param x X-coordinate of the pixel to retrieve.
 * @param y Y-coordinate of the pixel to retrieve.
 * @return The color of the pixel at the specified coordinates.
 */
unsigned int get_pixel_color(t_img *img, int x, int y)
{
    char *pixel_location;

    pixel_location = img->addr + (y * img->line_len + x * (img->bpp / 8));
    return *(unsigned int *)pixel_location;
}

// /**
//  * Draws a filled rectangle with a specified color onto an image.
//  * 
//  * @param img Pointer to the t_img structure representing the destination image.
//  * @param position The coordinates (x, y) of the top-left corner of the rectangle.
//  * @param dimensions The width and height of the rectangle.
//  * @param color Color to fill the rectangle with.
//  */
void draw_rectcurrent_angle(t_img *img, t_vector position, t_vector dimensions, int color)
{
    int x;
    int y;

    y = 0;
    while (y < dimensions.y)
    {
        x = 0;
        while (x < dimensions.x)
        {
            put_pixel(img, position.x + x, position.y + y, color);
            x++;
        }
        y++;
    }
}

/**
 * Copies pixels from one image to another, skipping a specified color.
 * 
 * @param offset Array containing the x and y offsets for positioning the 
 * source image on the destination image.
 * @param images Array containing two t_img structures: the source image
 * and the destination image.
 * @param color_to_skip Color to exclude from copying.
 */
void mlx_img_to_img(int p[2], t_img img[2], int c1)
{
    int xy[2];
    int color;

    xy[1] = 0;
    while (xy[1] < img[0].height)
    {
        xy[0] = 0;
        while (xy[0] < img[0].width)
        {
            if (xy[0] + p[0] >= 0 && xy[1] + p[1] >= 0)
            {
                color = get_pixel_color(&img[0], xy[0], xy[1]);
                if (color != c1)
                {
                    put_pixel(&img[1], xy[0] + p[0], xy[1] + p[1], color);
                }
            }
            xy[0]++;
        }
        xy[1]++;
    }
}

/**
 * Checks if the provided file path is valid for an image.
 * 
 * @param file_path The path to the image file.
 * @return 1 if the path is valid (i.e., ends with ".xpm"), otherwise 0.
 */
int is_valid_image_path(const char *file_path)
{
    return file_path && ft_strrncmp(file_path, ".xpm", 4) == 0;
}

/**
 * Allocates memory for a t_img structure and initializes it.
 * 
 * @return A pointer to the newly allocated t_img structure, or NULL if memory allocation fails.
 */
t_img *create_image_structure(void)
{
    t_img *image = malloc(sizeof(t_img));
    if (!image) 
        return (NULL);
    image->i = NULL;
    return (image);
}

/**
 * Loads an image from a file and initializes the given t_img structure.
 * 
 * @param mlx_ptr Pointer to the MLX (MiniLibX) instance used to load the image.
 * @param file_path Path to the image file.
 * @param image Pointer to the t_img structure to be initialized with the image data.
 * @return 1 if the image is successfully loaded, otherwise 0.
 */
int load_image_from_file(void *mlx_ptr, char *file_path, t_img *image)
{
    image->i = mlx_xpm_file_to_image(mlx_ptr, file_path, &image->width, &image->height);
    if (!image->i)
        return (0);
    image->addr = mlx_get_data_addr(image->i, &image->bpp, &image->line_len, &image->endian);
    return (1);
}

/**
 * Loads an image from a file and creates a t_img structure for it.
 * 
 * @param mlx_ptr Pointer to the MLX (MiniLibX) instance used for loading the image.
 * @param file_path Path to the image file (must be in .xpm format).
 * @return A pointer to a t_img structure containing the image data, or NULL if the image cannot be loaded.
 */
t_img *load_img(void *mlx_ptr, char *file_path)
{
    int file_descriptor;
    t_img *image;

    if (!is_valid_image_path(file_path))
        return NULL;
    file_descriptor = open(file_path, O_RDONLY);
    if (file_descriptor < 0)
        return NULL;
    close(file_descriptor);
    image = create_image_structure();
    if (!image)
        return NULL;
    if (!load_image_from_file(mlx_ptr, file_path, image))
    {
        free(image);
        return NULL;
    }
    return (image);
}
