/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 19:43:09 by mquero            #+#    #+#             */
/*   Updated: 2024/11/26 20:00:28 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void calcul_coord(t_gridval *gvals, t_coord *coord, int **matrix)
{

	gvals->z = matrix[gvals->row_count][gvals->j];
	isometric_projection1(gvals->row_count, gvals->j, gvals->z, coord);
	gvals->z = matrix[gvals->row_count][gvals->j + 1];
	isometric_projection2(gvals->row_count, gvals->j + 1, gvals->z, coord);
	coord->dx = abs(coord->iso_x - coord->dest_x);
	coord->dy = abs(coord->iso_y - coord->dest_y);
}

void calcul_coord_dest(t_gridval *gvals, t_coord *coord, int **matrix)
{
	gvals->z = matrix[gvals->row_count + 1][gvals->j];
	isometric_projection3(gvals->row_count + 1, gvals->j, gvals->z, coord);
	coord->dx = abs(coord->iso_x - coord->dest2_x);
	coord->dy = abs(coord->iso_y - coord->dest2_y);
}
void draw_map(mlx_image_t *img, int count, int nmb_count, int **matrix)
{
	t_gridval gvals;
	t_coord coord;

	gvals.row_count = 0;
	while (gvals.row_count + 1 < count)
	{
		gvals.j = 0;
		while (gvals.j + 1 < nmb_count)
		{
			calcul_coord(&gvals, &coord, matrix);
			if (coord.dx > coord.dy)
				line_algorithm(coord , coord.dest_x ,coord.dest_y, img);
			else
				line_slope_bigger(coord, coord.dest_x , coord.dest_y, img);
			calcul_coord_dest(&gvals, &coord, matrix);
			if (coord.dx > coord.dy)
				line_algorithm(coord , coord.dest2_x , coord.dest2_y, img);
			else
				line_slope_bigger(coord , coord.dest2_x , coord.dest2_y, img);
			gvals.j++;
		}
		gvals.row_count++;
	}
}
