/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:33:57 by mquero            #+#    #+#             */
/*   Updated: 2024/12/01 14:33:06 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_fdf.h"
// Exit the program as failure.
/**
 * Main MLX handle, carries important data in regards to the program.
 * @param window The window itself.
 * @param context Abstracted opengl data.
 * @param width The width of the window.
 * @param height The height of the window.
 * @param delta_time The time difference between the previous frame and the current frame.
 */

void manage_map(void* param)
{
	t_coord *coord = (t_coord*)param;
	// If we PRESS the 'J' key, print "Hello".
	if (mlx_is_key_down(coord->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(coord->mlx);
	if (mlx_is_key_down(coord->mlx, MLX_KEY_L))
	{
		coord->scale = coord->scale - 0.1;
		coord->height_scale = coord->scale - 0.1;
	}
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
	coord->scale = 20;
	coord->height_scale = 20;
	coord->a = 255;
	draw_map(coord);
	free(line);
	close(fd);
}

int32_t	main(int arg, char **args)
{
	t_coord coord;
	//mlx_t* mlx;
	//mlx_image_t* img;

	if (arg > 2)
		return 0;
	coord.mlx = mlx_init(WIDTH, HEIGHT, "Kero FDF", true);
	coord.img = mlx_new_image(coord.mlx, 4096, 2160);
	if (!coord.mlx)
		return 0;
	if (!coord.img || (mlx_image_to_window(coord.mlx,coord.img, 0, 0) < 0))
		return 0;
	start(args[1], &coord);
	//mlx_set_setting(MLX_MAXIMIZED, true);
	mlx_loop_hook(coord.mlx, &manage_map, &coord);
	mlx_loop_hook(coord.mlx, &draw_map, &coord);
	mlx_loop(coord.mlx);
	mlx_terminate(coord.mlx);
	freecolors(coord.colors, coord.total_rows);
	freematrix(coord.numbers, coord.total_rows);
}
