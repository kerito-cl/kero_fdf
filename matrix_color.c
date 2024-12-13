/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 12:04:18 by mquero            #+#    #+#             */
/*   Updated: 2024/12/13 08:53:05 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

unsigned int	*build_color_row(char *line)
{
	int				i;
	int				j;
	unsigned int	*row;
	int				count;
	char			**split;

	count = count_numbers(line);
	row = (unsigned int *)malloc(count * sizeof(unsigned int));
	if (row == NULL)
		return (NULL);
	split = ft_split(line, ' ');
	i = 0;
	while (split[i])
	{
		j = 0;
		while (split[i][j] != ',' && split[i][j] != '\0')
			j++;
		if (split[i][j] == ',')
			row[i] = ft_atoi(split[i] + j + 1);
		else
			row[i] = ft_atoi("0X009999");
		i++;
	}
	freesplit(split);
	return (row);
}

unsigned int	**color_matrix(int fd, char *map)
{
	unsigned int	**matrix;
	char			*line;
	int				i;
	int				count;

	i = 0;
	count = count_rows(fd);
	matrix = (unsigned int **)malloc(sizeof(unsigned int *) * count);
	if (matrix == NULL || count == 0)
		return (NULL);
	fd = close_and_read(fd, map);
	while (i < count)
	{
		line = get_next_line(fd);
		matrix[i] = build_color_row(line);
		if (matrix[i] == NULL)
		{
			freecolors(matrix, i);
			return (NULL);
		}
		free(line);
		i++;
	}
	return (matrix);
}

void	putcolors(t_coord *m)
{
	int				i;
	int				j;
	unsigned int	color;

	color = 0x009999;
	i = 0;
	while (i < m->total_rows)
	{
		j = 0;
		while (j < m->total_cols)
		{
			if (m->numbers[i][j] < 0 && m->colors[i][j] == color)
				m->colors[i][j] = color - (10 * m->numbers[i][j]);
			else if (m->numbers[i][j] > 0 && m->colors[i][j] == color)
				m->colors[i][j] = color * (20 * m->numbers[i][j]);
			j++;
		}
		i++;
	}
}
