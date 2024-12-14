/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:37:19 by mquero            #+#    #+#             */
/*   Updated: 2024/12/14 13:45:41 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

int	check_error(char *map)
{
	int	fd;

	fd = open(map, O_RDONLY);
	if (fd == -1)
		return (0);
	return (1);
}

void	free_all(t_coord *c)
{
	mlx_delete_image(c->mlx, c->img);
	mlx_terminate(c->mlx);
	if (c->colors != NULL)
		freecolors(c->colors, c->total_rows);
	if (c->numbers != NULL)
		freematrix(c->numbers, c->total_rows);
	exit(0);
}

void	throw_error(int flag)
{
	if (flag == 0)
	{
		perror("not passing correct arguments");
		exit(0);
	}
	if (flag == 1)
	{
		perror("Your map doesn't exist");
		exit(0);
	}
}

int	check_if_fdf(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '.' && str[i + 1] == 'f' && str[i + 2] == 'd'
			&& str[i + 3] == 'f')
			return (1);
		i++;
	}
	return (0);
}
