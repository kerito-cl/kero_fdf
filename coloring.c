/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coloring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 11:07:23 by mquero            #+#    #+#             */
/*   Updated: 2024/11/30 14:12:51 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void	bitwise_op1(t_matrix m, t_coord *coord, int row, int col)
{
	if (m.colors[row][col] <= 0XFF)
	{
		coord->r1 = 0;
		coord->g1 = 0;
		coord->b1 = (m.colors[row][col]) & 0xFF;
	}
	else if (m.colors[row][col] <= 0XFFFF)
	{
		coord->r1 = 0;
		coord->g1 = (m.colors[row][col] >> 8) & 0xFF;
		coord->b1 = (m.colors[row][col]) & 0xFF;
	}
	else if (m.colors[row][col] <= 0XFFFFFF)
	{
		coord->r1 = (m.colors[row][col] >> 16) & 0xFF;
		coord->g1 = (m.colors[row][col] >> 8) & 0xFF;
		coord->b1 = (m.colors[row][col]) & 0xFF;
	}
}

void	bitwise_op2(t_matrix m, t_coord *coord, int row, int col)
{
	if (m.colors[row][col] <= 0XFF)
	{
		coord->r2 = 0;
		coord->g2 = 0;
		coord->b2 = (m.colors[row][col + 1]) & 0xFF;
	}
	else if (m.colors[row][col] <= 0XFFFF)
	{
		coord->r2 = 0;
		coord->g2 = (m.colors[row][col] >> 8) & 0xFF;
		coord->b2 = (m.colors[row][col]) & 0xFF;
	}
	else if (m.colors[row][col + 1] <= 0XFFFFFF)
	{
		coord->r2 = (m.colors[row][col] >> 16) & 0xFF;
		coord->g2 = (m.colors[row][col] >> 8) & 0xFF;
		coord->b2 = (m.colors[row][col]) & 0xFF;
	}
}
void	set_color2(t_matrix m, t_coord *coord, int row, int col)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	bitwise_op2(m, coord, row + 1, col);
	r = coord->r1 + (coord->r2 - coord->r1) * 0.5;
	g = coord->g1 + (coord->g2 - coord->g1) * 0.5;
	b = coord->b1 + (coord->b2 - coord->b1) * 0.5;
	coord->final_color = (r << 24) + (g << 16) + (b << 8) + coord->a;
}

void	set_color1(t_matrix m, t_coord *coord, int row, int col)
{
	unsigned int r;
	unsigned int g;
	unsigned int b;

	bitwise_op1(m, coord, row, col);
	bitwise_op2(m, coord, row, col + 1);
	r = coord->r1 + (coord->r2 - coord->r1) * 0.5;
	g = coord->g1 + (coord->g2 - coord->g1) * 0.5;
	b = coord->b1 + (coord->b2 - coord->b1) * 0.5;
	coord->final_color = (r << 24) + (g << 16) + (b << 8) + coord->a;
}