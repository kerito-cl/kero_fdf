/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_algo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:31:04 by mquero            #+#    #+#             */
/*   Updated: 2024/12/14 10:12:29 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void	isometric_projection1(int i, int j, t_coord *c)
{
	double	scale;
	double	height_scale;

	scale = c->scale;
	height_scale = c->height_scale / 2;
	c->z = c->z * height_scale;
	c->iso_x = (j - i) * scale;
	c->iso_y = (j + i) * scale;
	rotate_z(&c->iso_x, &c->iso_y, c);
	rotate_y(&c->iso_x, &c->z, c);
	rotate_x(&c->iso_y, &c->z, c);
	c->iso_x = c->iso_x + c->x_offset;
	c->iso_y = c->iso_y + c->y_offset;
}

void	isometric_projection2(int i, int j, t_coord *c)
{
	double	scale;
	double	height_scale;

	scale = c->scale;
	height_scale = c->height_scale;
	c->z = c->z * height_scale / 2;
	c->dest_x = (j - i) * scale;
	c->dest_y = (j + i) * scale;
	rotate_z(&c->dest_x, &c->dest_y, c);
	rotate_y(&c->dest_x, &c->z, c);
	rotate_x(&c->dest_y, &c->z, c);
	c->dest_x = c->dest_x + c->x_offset;
	c->dest_y = c->dest_y + c->y_offset;
}

void	isometric_projection3(int i, int j, t_coord *c)
{
	double	scale;
	double	height_scale;

	scale = c->scale;
	height_scale = c->height_scale;
	c->z = c->z * height_scale / 2;
	c->dest2_x = (j - i) * scale;
	c->dest2_y = (j + i) * scale;
	rotate_z(&c->dest2_x, &c->dest2_y, c);
	rotate_y(&c->dest2_x, &c->z, c);
	rotate_x(&c->dest2_y, &c->z, c);
	c->dest2_x = c->dest2_x + c->x_offset;
	c->dest2_y = c->dest2_y + c->y_offset;
}

void	line_algorithm(t_coord c, int x2, int y2, mlx_image_t *img)
{
	int	pixel;

	c.dx = abs(x2 - c.iso_x);
	c.dy = abs(y2 - c.iso_y);
	pixel = (2 * c.dy) - c.dx;
	while (c.iso_x < x2 || c.iso_x > x2)
	{
		if ((uint64_t)c.iso_x < (uint64_t)c.width
			&& (uint64_t)c.iso_y < (uint64_t)c.height)
			mlx_put_pixel(img, c.iso_x, c.iso_y, c.final_color);
		if (c.iso_x < x2)
			c.iso_x = c.iso_x + 1;
		else
			c.iso_x = c.iso_x - 1;
		if (pixel < 0)
			pixel = pixel + (2 * c.dy);
		else
		{
			pixel = pixel + (2 * c.dy) - (2 * c.dx);
			if (c.iso_y < y2)
				c.iso_y = c.iso_y + 1;
			else
				c.iso_y = c.iso_y - 1;
		}
	}
}

void	line_slope_bigger(t_coord c, int x2, int y2, mlx_image_t *img)
{
	int	pixel;

	c.dx = abs(x2 - c.iso_x);
	c.dy = abs(y2 - c.iso_y);
	pixel = (2 * c.dx) - c.dy;
	while (c.iso_y < y2 || c.iso_y > y2)
	{
		if ((uint64_t)c.iso_x < (uint64_t)c.width
			&& (uint64_t)c.iso_y < (uint64_t)c.height)
			mlx_put_pixel(img, c.iso_x, c.iso_y, c.final_color);
		if (c.iso_y < y2)
			c.iso_y = c.iso_y + 1;
		else
			c.iso_y = c.iso_y - 1;
		if (pixel < 0)
			pixel = pixel + (2 * c.dx);
		else
		{
			pixel = pixel + (2 * c.dx) - (2 * c.dy);
			if (c.iso_x < x2)
				c.iso_x = c.iso_x + 1;
			else
				c.iso_x = c.iso_x - 1;
		}
	}
}
