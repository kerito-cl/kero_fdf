/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 19:43:09 by mquero            #+#    #+#             */
/*   Updated: 2024/11/27 11:05:44 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"
void	set_color_base(t_coord *coord)
{

	coord->r = 255;
	coord->g = 255;
	coord->b = 255;
	coord->a = 255;
	coord->color = (coord->r << 24) + (coord->g << 16) + (coord->b << 8)
		+ coord->a;
}
void	calcul_color(t_coord *coord, int z)
{
	coord->r = coord->r;
	coord->g = coord->g - (z * 5);
	coord->b = coord->b - (z * 5);
	coord->a = 255;
	if (coord->g <= 0 && coord->b <= 0)
		coord->r = coord->r - (z * 5);
	coord->color = (coord->r << 24) + (coord->g << 16) + (coord->b << 8)
		+ coord->a;
}
void	calcul_coord(t_gridval *gvals, t_coord *coord, int **matrix)
{
	int	k;

	gvals->z = matrix[gvals->row_count][gvals->j];
	coord->hold_height = gvals->z;
	isometric_projection1(gvals->row_count, gvals->j, gvals->z, coord);
	gvals->z = matrix[gvals->row_count][gvals->j + 1];
	k = gvals->z;
	isometric_projection2(gvals->row_count, gvals->j + 1, gvals->z, coord);
	coord->dx = abs(coord->iso_x - coord->dest_x);
	coord->dy = abs(coord->iso_y - coord->dest_y);
	if (k - coord->hold_height != 0)
		calcul_color(coord, gvals->z);
}

void	calcul_coord_dest(t_gridval *gvals, t_coord *coord, int **matrix)
{
	int	k;
	gvals->z = matrix[gvals->row_count + 1][gvals->j];
	isometric_projection3(gvals->row_count + 1, gvals->j, gvals->z, coord);
	coord->dx = abs(coord->iso_x - coord->dest2_x);
	coord->dy = abs(coord->iso_y - coord->dest2_y);
	if (k - coord->hold_height != 0)
		calcul_color(coord, gvals->z);
}
void	draw_map(mlx_image_t *img, int count, int nmb_count, int **matrix)
{
	t_gridval	gvals;
	t_coord		coord;

	set_color_base(&coord);
	gvals.row_count = 0;
	while (gvals.row_count + 1 < count)
	{
		gvals.j = 0;
		while (gvals.j + 1 < nmb_count)
		{
			calcul_coord(&gvals, &coord, matrix);
			if (coord.dx > coord.dy)
				line_algorithm(coord, coord.dest_x, coord.dest_y, img);
			else
				line_slope_bigger(coord, coord.dest_x, coord.dest_y, img);
			calcul_coord_dest(&gvals, &coord, matrix);
			if (coord.dx > coord.dy)
				line_algorithm(coord, coord.dest2_x, coord.dest2_y, img);
			else
				line_slope_bigger(coord, coord.dest2_x, coord.dest2_y, img);
			gvals.j++;
		}
		gvals.row_count++;
	}
}
