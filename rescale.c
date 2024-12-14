/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rescale.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 11:28:22 by mquero            #+#    #+#             */
/*   Updated: 2024/12/14 13:04:16 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void	find_min_max(t_coord *c, int rows, int cols)
{
	int	j;
	int	i;

	i = 0;
	c->set_min = c->numbers[0][0];
	c->set_max = c->numbers[0][0];
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			if (c->numbers[i][j] < c->set_min)
				c->set_min = c->numbers[i][j];
			if (c->numbers[i][j] > c->set_max)
				c->set_max = c->numbers[i][j];
			j++;
		}
		i++;
	}
}

bool	has_values_greater_than_350(t_coord *c, int rows, int cols)
{
	int	j;
	int	i;

	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			if (c->numbers[i][j] > 350)
			{
				return (true);
			}
			j++;
		}
		i++;
	}
	return (false);
}

void	rescale_grid(t_coord *c, int rows, int cols)
{
	int	new_max;
	int	new_min;
	int	j;
	int	i;

	new_max = 20;
	new_min = 0;
	i = 0;
	if (has_values_greater_than_350(c, rows, cols))
	{
		find_min_max(c, rows, cols);
		while (i < rows)
		{
			j = 0;
			while (j < cols)
			{
				c->numbers[i][j] = (int)(((double)(c->numbers[i][j]
								- c->set_min) / (c->set_max - c->set_min))
						* (new_max - new_min) + new_min);
				j++;
			}
			i++;
		}
	}
}
