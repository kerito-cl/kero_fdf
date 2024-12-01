/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:33:57 by mquero            #+#    #+#             */
/*   Updated: 2024/12/01 22:43:09 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_fdf.h"
// Exit the program as failure.

void manage_map(void* param)
{
	t_coord *coord = (t_coord*)param;
	// If we PRESS the 'J' key, print "Hello".
	if (mlx_is_key_down(coord->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(coord->mlx);
	if (mlx_is_key_down(coord->mlx, MLX_KEY_L) && coord->scale >= 1)
	{
		coord->scale = coord->scale - 0.1;
		coord->height_scale = coord->height_scale - 0.1;
	}
	if (mlx_is_key_down(coord->mlx, MLX_KEY_K))
	{
		coord->scale = coord->scale + 0.1;
		coord->height_scale = coord->height_scale + 0.1;
	}
	if (mlx_is_key_down(coord->mlx, MLX_KEY_O))
		coord->height_scale = coord->height_scale + 0.1;
	if (mlx_is_key_down(coord->mlx, MLX_KEY_I))
		coord->height_scale = coord->height_scale - 0.1;
	if (mlx_is_key_down(coord->mlx, MLX_KEY_LEFT))
		coord->x_offset -= 4;
	if (mlx_is_key_down(coord->mlx, MLX_KEY_RIGHT))
		coord->x_offset += 4;
	if (mlx_is_key_down(coord->mlx, MLX_KEY_UP))
		coord->y_offset -= 4;
	if (mlx_is_key_down(coord->mlx, MLX_KEY_DOWN))
		coord->y_offset += 4;
	if (mlx_is_key_down(coord->mlx, MLX_KEY_D))
		coord->alpha = coord->alpha + 0.01;
	if (mlx_is_key_down(coord->mlx, MLX_KEY_A))
		coord->tetha = coord->tetha + 0.01;
	if (mlx_is_key_down(coord->mlx, MLX_KEY_W))
		coord->gamma = coord->gamma + 0.01;
}

void	start(char *map,t_coord *coord)
{
	char *line;
	int	fd;

    fd = open(map, O_RDONLY);
	coord->numbers = create_matrix(fd, map);
	fd = close_and_read(fd, map);
	coord->colors = color_matrix(fd, map);
	fd = close_and_read(fd, map);
	line = get_next_line(fd);
	coord->total_cols = count_numbers(line);
	coord->total_rows = count_rows(fd) + 1;
	putcolors(coord);
	coord->scale = 1;
	coord->height_scale = 1;
	coord->width = 1980;
	coord->height = 1080;
	coord->a = 255;
	coord->alpha = 1.134;
	coord->tetha = 0;
	coord->gamma = 0;
	coord->x_offset = 1980/2;
	coord->y_offset = 1080/2;
	draw_map(coord);
	free(line);
	close(fd);
}

int32_t	main(int arg, char **args)
{
	t_coord coord;

	if (arg > 2)
		return 0;
	coord.mlx = mlx_init(WIDTH, HEIGHT, "Kero FDF", true);
	coord.img = mlx_new_image(coord.mlx, WIDTH, HEIGHT);
	if (!coord.mlx)
		return 0;
	if (!coord.img || (mlx_image_to_window(coord.mlx,coord.img, 0, 0) < 0))
		return 0;
	start(args[1], &coord);
	mlx_set_setting(MLX_MAXIMIZED, true);
	mlx_loop_hook(coord.mlx, &manage_map, &coord);
	mlx_loop_hook(coord.mlx, &draw_map, &coord);
	mlx_loop(coord.mlx);
	mlx_terminate(coord.mlx);
	freecolors(coord.colors, coord.total_rows);
	freematrix(coord.numbers, coord.total_rows);
}
