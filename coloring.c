/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coloring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 11:07:23 by mquero            #+#    #+#             */
/*   Updated: 2024/12/02 13:35:54 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void	bitwise_op1(t_coord *c, int row, int col)
{
	if (c->colors[row][col] <= 0XFF)
	{
		c->r1 = 0;
		c->g1 = 0;
		c->b1 = (c->colors[row][col]) & 0xFF;
	}
	else if (c->colors[row][col] <= 0XFFFF)
	{
		c->r1 = 0;
		c->g1 = (c->colors[row][col] >> 8) & 0xFF;
		c->b1 = (c->colors[row][col]) & 0xFF;
	}
	else if (c->colors[row][col] <= 0XFFFFFF)
	{
		c->r1 = (c->colors[row][col] >> 16) & 0xFF;
		c->g1 = (c->colors[row][col] >> 8) & 0xFF;
		c->b1 = (c->colors[row][col]) & 0xFF;
	}
}

void	bitwise_op2(t_coord *c, int row, int col)
{
	if (c->colors[row][col] <= 0XFF)
	{
		c->r2 = 0;
		c->g2 = 0;
		c->b2 = (c->colors[row][col + 1]) & 0xFF;
	}
	else if (c->colors[row][col] <= 0XFFFF)
	{
		c->r2 = 0;
		c->g2 = (c->colors[row][col] >> 8) & 0xFF;
		c->b2 = (c->colors[row][col]) & 0xFF;
	}
	else if (c->colors[row][col + 1] <= 0XFFFFFF)
	{
		c->r2 = (c->colors[row][col] >> 16) & 0xFF;
		c->g2 = (c->colors[row][col] >> 8) & 0xFF;
		c->b2 = (c->colors[row][col]) & 0xFF;
	}
}

void	set_color2(t_coord *c, int row, int col)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	bitwise_op2(c, row + 1, col);
	r = c->r1 + (c->r2 - c->r1) * 0.5;
	g = c->g1 + (c->g2 - c->g1) * 0.5;
	b = c->b1 + (c->b2 - c->b1) * 0.5;
	c->final_color = (r << 24) + (g << 16) + (b << 8) + c->a;
}

void	set_color1(t_coord *c, int row, int col)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	bitwise_op1(c, row, col);
	bitwise_op2(c, row, col + 1);
	r = c->r1 + (c->r2 - c->r1) * 0.5;
	g = c->g1 + (c->g2 - c->g1) * 0.5;
	b = c->b1 + (c->b2 - c->b1) * 0.5;
	c->final_color = (r << 24) + (g << 16) + (b << 8) + c->a;
}
