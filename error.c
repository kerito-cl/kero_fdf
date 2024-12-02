/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:37:19 by mquero            #+#    #+#             */
/*   Updated: 2024/12/02 14:47:03 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

int	helper(char **split, char *line, int fd, int j)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	if (j != i)
	{
		free(line);
		freesplit(split);
		close(fd);
		return (0);
	}
	free(line);
	freesplit(split);
	return (1);
}

int	check_error(char *map)
{
	int		fd;
	char	*line;
	char	**split;
	int		j;

	fd = open(map, O_RDONLY);
	if (fd == -1)
		return (0);
	line = get_next_line(fd);
	split = ft_split(line, ' ');
	while (split[j])
		j++;
	freesplit(split);
	free(line);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			return (1);
		split = ft_split(line, ' ');
		if (helper(split, line, fd, j) == 0)
			return (0);
	}
}

void	free_all(t_coord *c)
{
	mlx_delete_image(c->mlx, c->img);
	mlx_terminate(c->mlx);
	freecolors(c->colors, c->total_rows);
	freematrix(c->numbers, c->total_rows);
}
