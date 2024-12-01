/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_algo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:31:04 by mquero            #+#    #+#             */
/*   Updated: 2024/12/01 22:29:02 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void	rotate_z(int *x, int *y, t_coord *coord)
{
	double calc_x;
	double calc_y;

	calc_x = roundf(*x * cos(coord->gamma) - (*y * sin(coord->gamma)));
	calc_y = roundf(*x * sin(coord->gamma) + (*y * cos(coord->gamma)));
	*x = calc_x;
	*y = calc_y;
}
void	rotate_y(int *x, int *z, t_coord *coord)
{
	double calc_x;
	double calc_z;

	calc_x = roundf(*x * cos(coord->tetha) + (*z * sin(coord->tetha)));
	calc_z = roundf(*z * cos(coord->tetha) - (*x * sin(coord->tetha)));
	*x = calc_x;
	*z = calc_z;
}
void	rotate_x(int *y, int *z, t_coord *coord)
{
	double calc_z;
	double calc_y;

	calc_y = roundf(*y * cos(coord->alpha) - (*z * sin(coord->alpha)));
	calc_z = roundf(*y * sin(coord->alpha) + (*z * cos(coord->alpha)));
	*y = calc_y;
	*z = calc_z;
}

void	isometric_projection1(int i, int j, int z, t_coord *coord)
{
	double		scale;
	double	calc_x;
	double	calc_y;
	double	height_scale;

	scale = coord->scale;
	height_scale = coord->height_scale;
	coord->z = coord->z * height_scale;
	coord->iso_x = (j - i) * scale;
	coord->iso_y = (j + i) * scale;
	rotate_z(&coord->iso_x, &coord->iso_y ,coord);
	rotate_y(&coord->iso_x, &coord->z, coord);
	rotate_x(&coord->iso_y, &coord->z, coord);
	coord->iso_x = coord->iso_x + coord->x_offset;
	coord->iso_y = coord->iso_y + coord->y_offset;
}

void	isometric_projection2(int i, int j, int z, t_coord *coord)
{
	double		scale;
	double	calc_x;
	double	calc_y;
	double	height_scale;

	scale = coord->scale;
	height_scale = coord->height_scale;
	coord->z = coord->z * height_scale;
	coord->dest_x = (j - i) * scale;
	coord->dest_y = (j + i) * scale;
	rotate_z(&coord->dest_x, &coord->dest_y ,coord);
	rotate_y(&coord->dest_x, &coord->z, coord);
	rotate_x(&coord->dest_y, &coord->z, coord);
	coord->dest_x = coord->dest_x + coord->x_offset;
	coord->dest_y = coord->dest_y + coord->y_offset;
}

void	isometric_projection3(int i, int j, int z, t_coord *coord)
{
	double		scale;
	double	calc_x;
	double	calc_y;
	double	height_scale;

	scale = coord->scale;
	height_scale = coord->height_scale;
	coord->z = coord->z * height_scale;
	coord->dest2_x = (j - i) * scale;
	coord->dest2_y = (j + i) * scale;
	rotate_z(&coord->dest2_x, &coord->dest2_y ,coord);
	rotate_y(&coord->dest2_x, &coord->z, coord);
	rotate_x(&coord->dest2_y, &coord->z, coord);
	coord->dest2_x = coord->dest2_x + coord->x_offset;
	coord->dest2_y = coord->dest2_y + coord->y_offset;
}

void	line_algorithm(t_coord coord, int x2, int y2, mlx_image_t *img)
{
	int	pixel;

	coord.dx = abs(x2 - coord.iso_x);
	coord.dy = abs(y2 - coord.iso_y);
	pixel = (2 * coord.dy) - coord.dx;
	while (coord.iso_x < x2 || coord.iso_x > x2)
	{
		if ((unsigned int)coord.iso_x < coord.width && (unsigned int)coord.iso_y < coord.height)
			mlx_put_pixel(img, coord.iso_x, coord.iso_y, coord.final_color);
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

void	line_slope_bigger(t_coord coord, int x2, int y2, mlx_image_t *img)
{
	int pixel;

	coord.dx = abs(x2 - coord.iso_x);
	coord.dy = abs(y2 - coord.iso_y);
	pixel = (2 * coord.dx) - coord.dy;
	while (coord.iso_y < y2 || coord.iso_y > y2)
	{
		if ((unsigned int)coord.iso_x < coord.width && (unsigned int)coord.iso_y < coord.height)
			mlx_put_pixel(img, coord.iso_x, coord.iso_y, coord.final_color);
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