/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 19:43:09 by mquero            #+#    #+#             */
/*   Updated: 2024/11/28 16:12:54 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"
void	save_color(t_coord *coord)
{
	unsigned int r;
	unsigned int g;
	unsigned int b;

	coord->sr = coord->r2;
	coord->sg = coord->g2;
	coord->sb = coord->b2;
}

void	set_color_base(t_coord *coord)
{

	coord->r2 = 255;
	coord->g2 = 255;
	coord->b2 = 255;
	coord->a = 255;
	coord->final_color = (coord->r2 << 24) + (coord->g2 << 16) + (coord->b2 << 8)
		+ coord->a;
}
void	set_color(t_coord *coord)
{

	coord->r1 = coord->sr;
	coord->g1 = coord->sg;
	coord->b1 = coord->sb;
	coord->a = 255;
	coord->final_color = (coord->r1 << 24) + (coord->g1 << 16) + (coord->b1 << 8)
		+ coord->a;
}
unsigned int	calcul_init_color(t_coord *coord, int z)
{
	if (coord->g2 >= 255 && coord->b2 >= 255 && coord->r2 >= 255)
		coord->r2 = coord->r2 - abs(z*10);
	else if (coord->r2 >= 255 && coord->b2 <= 0)
		coord->g2 = coord->g1 + abs(z*10);
	else if (coord->g2 <= 0 && coord->b2 <= 0)
		coord->r2 = coord->r2 + abs(z*10);
	else if (coord->r2 <= 0)
		coord->r2 = coord->r2 + abs(z*10);
	else
		coord->b2 = coord->b2 + abs(z*10);
	coord->dest1_color = (coord->r2 << 24) + (coord->g2 << 16) + (coord->b2 << 8)
		+ coord->a;
	return (coord->dest1_color);
}

unsigned int	calcul_dest_color(t_coord *coord, int z)
{
	if (coord->g2 <= 0 && coord->b2 <= 0)
	{
		coord->r2 = coord->r1 - abs(z*10);
		coord->g2 = 0;
		coord->b2 = 0;
	}
	else if (coord->r2 == 255 && coord->g2 == 255)
		coord->b2 = coord->b1 - abs(z*10);
	else if (coord->b2 <= 0 && coord->r2 == 255)
	{
		coord->g2 = coord->g1 - abs(z*10);
		coord->b2 = 0;
	}
	else if (coord->r2 <= 0)
		coord->r2 = 0;
	coord->dest2_color = (coord->r2 << 24) + (coord->g2 << 16) + (coord->b2 << 8)
		+ coord->a;
	return (coord->dest2_color);
}
void	calcul_coord(t_gridval *gvals, t_coord *coord, int **matrix)
{
	int	k;

	set_color(coord);
	gvals->z = matrix[gvals->row_count][gvals->j];
	coord->hold_height = gvals->z;
	isometric_projection1(gvals->row_count, gvals->j, gvals->z, coord);
	gvals->z = matrix[gvals->row_count][gvals->j + 1];
	k = gvals->z;
	isometric_projection2(gvals->row_count, gvals->j + 1, gvals->z, coord);
	coord->dx = abs(coord->iso_x - coord->dest_x);
	coord->dy = abs(coord->iso_y - coord->dest_y);
	if (k == coord->hold_height)
		return ;
	if (coord->hold_height > k )
		calcul_init_color(coord,coord->hold_height - k);
	else
		coord->final_color = calcul_dest_color(coord, k - coord->hold_height);
	save_color(coord);
}

void	calcul_coord_dest(t_gridval *gvals, t_coord *coord, int **matrix)
{
	int	k;

	gvals->z = matrix[gvals->row_count + 1][gvals->j];
	k = gvals->z;
	isometric_projection3(gvals->row_count + 1, gvals->j, gvals->z, coord);
	coord->dx = abs(coord->iso_x - coord->dest2_x);
	coord->dy = abs(coord->iso_y - coord->dest2_y);
	if (k == coord->hold_height)
		return ;
	if (coord->hold_height > k )
		calcul_init_color(coord,coord->hold_height - k);
	else
		coord->final_color = calcul_dest_color(coord, k - coord->hold_height);
}
void	draw_map(mlx_image_t *img, int count, int nmb_count, int **matrix)
{
	t_gridval	gvals;
	t_coord		coord;

	set_color_base(&coord);
	save_color(&coord);
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
		set_color_base(&coord);
		save_color(&coord);
	}
}