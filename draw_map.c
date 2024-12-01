/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 19:43:09 by mquero            #+#    #+#             */
/*   Updated: 2024/12/01 14:38:39 by mquero           ###   ########.fr       */
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
void	calcul_coord(t_gridval *gvals, t_coord *coord)
{
	coord->z = coord->numbers[gvals->row_count][gvals->j];
	isometric_projection1(gvals->row_count, gvals->j, coord->z, coord);
	coord->z = coord->numbers[gvals->row_count][gvals->j + 1];
	isometric_projection2(gvals->row_count, gvals->j + 1, coord->z, coord);
	set_color1(coord, gvals->row_count, gvals->j);
	coord->dx = abs(coord->iso_x - coord->dest_x);
	coord->dy = abs(coord->iso_y - coord->dest_y);
}

void	calcul_coord_dest(t_gridval *gvals, t_coord *coord)
{
	coord->z = coord->numbers[gvals->row_count + 1][gvals->j];
	isometric_projection3(gvals->row_count + 1, gvals->j, coord->z, coord);
	set_color2(coord, gvals->row_count, gvals->j);
	coord->dx = abs(coord->iso_x - coord->dest2_x);
	coord->dy = abs(coord->iso_y - coord->dest2_y);
}
void	draw_map(void *param)
{
	t_gridval	gvals;
	t_coord	*coord;

	coord = (t_coord *)param;
	redraw_map(coord->img);
	gvals.row_count = 0;
	while (gvals.row_count + 1 < coord->total_rows)
	{
		gvals.j = 0;
		while (gvals.j + 1 < coord->total_cols)
		{
			calcul_coord(&gvals, coord);
			if (coord->dx > coord->dy)
				line_algorithm(*coord, coord->dest_x, coord->dest_y, coord->img);
			else
				line_slope_bigger(*coord, coord->dest_x, coord->dest_y, coord->img);
			calcul_coord_dest(&gvals, coord);
			if (coord->dx > coord->dy)
				line_algorithm(*coord, coord->dest2_x, coord->dest2_y, coord->img);
			else
				line_slope_bigger(*coord, coord->dest2_x, coord->dest2_y, coord->img);
			gvals.j++;
		}
		gvals.row_count++;
	}
}