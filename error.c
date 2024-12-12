/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:37:19 by mquero            #+#    #+#             */
/*   Updated: 2024/12/11 11:53:47 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

int	check_error(char *map)
{
	int		fd;

	fd = open(map, O_RDONLY);
	if (fd == -1)
		return (0);
	return (1);
}

void	free_all(t_coord *c)
{
	mlx_delete_image(c->mlx, c->img);
	mlx_terminate(c->mlx);
	freecolors(c->colors, c->total_rows);
	freematrix(c->numbers, c->total_rows);
}
