/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:33:57 by mquero            #+#    #+#             */
/*   Updated: 2024/12/11 14:48:24 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"
#include <string.h>

void	manage_rotation(void *param)
{
	t_coord	*c;

	c = (t_coord *)param;
	if (mlx_is_key_down(c->mlx, MLX_KEY_D))
		c->alpha = c->alpha + 0.01;
	if (mlx_is_key_down(c->mlx, MLX_KEY_A))
		c->alpha = c->alpha - 0.01;
	if (mlx_is_key_down(c->mlx, MLX_KEY_W))
		c->tetha = c->tetha + 0.01;
	if (mlx_is_key_down(c->mlx, MLX_KEY_S))
		c->tetha = c->tetha - 0.01;
	if (mlx_is_key_down(c->mlx, MLX_KEY_Q))
		c->gamma = c->gamma - 0.01;
	if (mlx_is_key_down(c->mlx, MLX_KEY_E))
		c->gamma = c->gamma + 0.01;
	if (mlx_is_key_down(c->mlx, MLX_KEY_LEFT))
		c->x_offset -= 4;
	if (mlx_is_key_down(c->mlx, MLX_KEY_RIGHT))
		c->x_offset += 4;
	if (mlx_is_key_down(c->mlx, MLX_KEY_UP))
		c->y_offset -= 4;
	if (mlx_is_key_down(c->mlx, MLX_KEY_DOWN))
		c->y_offset += 4;
}

void	manage_map(void *param)
{
	t_coord	*c;

	c = (t_coord *)param;
	if (mlx_is_key_down(c->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(c->mlx);
	if (mlx_is_key_down(c->mlx, MLX_KEY_L) && c->scale >= 1)
	{
		c->scale = c->scale - 0.1;
		c->height_scale = c->height_scale - 0.1;
	}
	if (mlx_is_key_down(c->mlx, MLX_KEY_K))
	{
		c->scale = c->scale + 0.1;
		c->height_scale = c->height_scale + 0.1;
	}
	if (mlx_is_key_down(c->mlx, MLX_KEY_O))
		c->height_scale = c->height_scale + 0.1;
	if (mlx_is_key_down(c->mlx, MLX_KEY_I))
		c->height_scale = c->height_scale - 0.1;
}

void	set_values(t_coord *c)
{
	c->width = 1980;
	c->height = 1080;
	c->scale = c->height / c->total_cols / 2;
	c->height_scale = c->scale;
	c->a = 255;
	c->alpha = 1.134;
	c->tetha = 0;
	c->gamma = 0;
	c->x_offset = 1980 / 2;
	c->y_offset = 1080 / 2;
}

void	start(char *map, t_coord *c)
{
	char	*line;
	int		fd;

	fd = open(map, O_RDONLY);
	if (fd == -1)
		exit(0);
	c->numbers = create_matrix(fd, map);
	fd = close_and_read(fd, map);
	c->colors = color_matrix(fd, map);
	fd = close_and_read(fd, map);
	if (c->numbers == NULL || c->colors == NULL)
		exit(1);
	line = get_next_line(fd);
	if (line == NULL)
	{
		free_all(c);
		exit(0);
	}
	c->total_cols = count_numbers(line);
	c->total_rows = count_rows(fd) + 1;
	set_values(c);
	putcolors(c);
	draw_map(c);
	free(line);
	close(fd);
}

int32_t	main(int arg, char **args)
{
	t_coord	c;

	if (arg != 2)
	{
		perror("not passing correct arguments");
		return (0);
	}
	if (check_error(args[1]) == 0)
	{
		perror("Your map doesn't exist");
		return (0);
	}
	c.mlx = mlx_init(WIDTH, HEIGHT, "Kero FDF", true);
	if (!c.mlx)
		return (0);
	c.img = mlx_new_image(c.mlx, WIDTH, HEIGHT);
	if (!c.img || (mlx_image_to_window(c.mlx, c.img, 0, 0) < 0))
		return (0);
	start(args[1], &c);
	mlx_loop_hook(c.mlx, &manage_map, &c);
	mlx_loop_hook(c.mlx, &manage_rotation, &c);
	mlx_loop_hook(c.mlx, &draw_map, &c);
	mlx_loop(c.mlx);
	free_all(&c);
}
