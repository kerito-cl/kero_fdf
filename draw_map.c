/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 19:43:09 by mquero            #+#    #+#             */
/*   Updated: 2024/12/02 13:37:27 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void	redraw_map(mlx_image_t *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			mlx_put_pixel(img, j, i, 0);
			j++;
		}
		i++;
	}
}
void	calcul_coord(t_coord *c)
{
	c->z = c->numbers[c->row_count][c->j];
	isometric_projection1(c->row_count, c->j, c->z, c);
	c->z = c->numbers[c->row_count][c->j + 1];
	isometric_projection2(c->row_count, c->j + 1, c->z, c);
	set_color1(c, c->row_count, c->j);
	c->dx = abs(c->iso_x - c->dest_x);
	c->dy = abs(c->iso_y - c->dest_y);
}

void	calcul_coord_dest(t_coord *c)
{
	c->z = c->numbers[c->row_count + 1][c->j];
	isometric_projection3(c->row_count + 1, c->j, c->z, c);
	set_color2(c, c->row_count, c->j);
	c->dx = abs(c->iso_x - c->dest2_x);
	c->dy = abs(c->iso_y - c->dest2_y);
}
void	draw_map(void *param)
{
	t_coord *c;

	c = (t_coord *)param;
	redraw_map(c->img);
	c->row_count = 0;
	while (c->row_count + 1 < c->total_rows)
	{
		c->j = 0;
		while (c->j + 1 < c->total_cols)
		{
			calcul_coord(c);
			if (c->dx > c->dy)
				line_algorithm(*c, c->dest_x, c->dest_y, c->img);
			else
				line_slope_bigger(*c, c->dest_x, c->dest_y, c->img);
			calcul_coord_dest(c);
			if (c->dx > c->dy)
				line_algorithm(*c, c->dest2_x, c->dest2_y, c->img);
			else
				line_slope_bigger(*c, c->dest2_x, c->dest2_y, c->img);
			c->j++;
		}
		c->row_count++;
	}
}