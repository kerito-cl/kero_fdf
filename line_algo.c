/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_algo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:31:04 by mquero            #+#    #+#             */
/*   Updated: 2024/11/26 22:11:09 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_fdf.h"

void isometric_projection1(int i, int j, int z, t_coord *coord) 
{
	int	scale;
	double calc_x;
	double calc_y;
	double height_scale;

	scale = SCALE;
	height_scale = HEIGHT_SCALE;
    calc_x = roundf(((j - i) * scale * cos(ANGLE)));
    calc_y = roundf((((i + j) * scale * sin(ANGLE))) - (z * height_scale));
	coord->iso_x = calc_x + (WIDTH / 2);
	coord->iso_y = calc_y + (HEIGHT / 2);
}

void isometric_projection2(int i, int j, int z, t_coord *coord) 
{
	int	scale;
	double calc_x;
	double calc_y;
	double height_scale;

	scale = SCALE;
	height_scale = HEIGHT_SCALE;
    calc_x = roundf((j - i) * scale * cos(ANGLE));
    calc_y = roundf(((i + j) * (scale) * sin(ANGLE)) - (z * height_scale));
	coord->dest_x = calc_x + (WIDTH / 2);
	coord->dest_y = calc_y + (HEIGHT / 2);
}

void isometric_projection3(int i, int j, int z, t_coord *coord) 
{
	int	scale;
	double calc_x;
	double calc_y;
	double height_scale;

	scale = SCALE;
	height_scale = HEIGHT_SCALE;
    calc_x = roundf((j - i) * scale * cos(ANGLE));
    calc_y = roundf(((i + j) * scale * sin(ANGLE)) - (z * height_scale));
	coord->dest2_x = calc_x + (WIDTH / 2);
	coord->dest2_y = calc_y + (HEIGHT / 2);
}

void	line_algorithm(t_coord coord, int x2, int y2, mlx_image_t* img)
{
	int	pixel;

	coord.dx = abs(x2 - coord.iso_x);
	coord.dy = (y2 - coord.iso_y);
	pixel = (2 * coord.dy) - coord.dx;
	while (coord.iso_x < x2 || coord.iso_x > x2)
	{
		mlx_put_pixel(img, coord.iso_x , coord.iso_y, 0xFF0000FF+coord.dx);
		if (coord.iso_x < x2)
			coord.iso_x = coord.iso_x + 1;
		else
			coord.iso_x = coord.iso_x - 1;
		if (pixel < 0)
			pixel = pixel + (2 * coord.dy);
		else
		{
			pixel = pixel + (2 * coord.dy) - (2 * coord.dx);
			if (coord.iso_y < y2)
				coord.iso_y = coord.iso_y + 1;
			else
				coord.iso_y = coord.iso_y - 1;
		}
	}
}

void	line_slope_bigger(t_coord coord, int x2, int y2, mlx_image_t* img)
{
	int	pixel;

	coord.dx = abs(x2 - coord.iso_x);
	coord.dy = abs(y2 - coord.iso_y);
	pixel = (2 * coord.dx) - coord.dy;
	while (coord.iso_y < y2 || coord.iso_y > y2)
	{
		mlx_put_pixel(img, coord.iso_x , coord.iso_y, 0xFF0000FF);
		if (coord.iso_y < y2)
			coord.iso_y = coord.iso_y + 1;
		else
			coord.iso_y = coord.iso_y - 1;
		if (pixel < 0)
			pixel = pixel + (2 * coord.dx);
		else
		{
			pixel = pixel + (2 * coord.dx) - (2 * coord.dy);
			if (coord.iso_x < x2)
				coord.iso_x = coord.iso_x + 1;
			else
				coord.iso_x = coord.iso_x - 1;
		}
	}
}