/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 12:04:18 by mquero            #+#    #+#             */
/*   Updated: 2024/11/25 22:01:02 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"


int	close_and_read(int fd, char *map)
{
	close(fd);
    fd = open(map, O_RDONLY);
	return (fd);
}
int	count_numbers(char *line)
{
	int i;
	int	count;

	i = 0;
	count = 0;
	if (line[i] < '0' || line[i] > '9')
		return (0);
	while (line[i])
	{
		while ((line[i] >= '0' && line[i] <= '9') || line[i] == ' ')
		{
			i++;
			if (line[i] == ' ' && ft_isdigit(line[i + 1]) == 1)
				count++;
		}
		if (line[i] != '\n')
			return (0);
		count++;
		i++;
	}
	return	(count);
}
// Print the window width and height.
int	*build_row(char *line)
{
    int	i;
	int	j;
	int	*row;
	int	count;
	int	hold;

	count = count_numbers(line);
	row = (int *)malloc(count * sizeof(int));
	if (row == NULL || count == 0)
	{
		free(row);
		return (NULL);
	}
	j = 0;
	i = 0;
	hold = 0;
	while (line[i])
	{
		if (line[i] == ' ' && ft_isdigit(line[i + 1]) == 1)
		{
			row[j] = ft_atoi(line + hold);
			hold = i + 1;
			j++;
		}
		i++;
	}
	row[j] = ft_atoi(line + hold);
	return (row);
}

int count_rows(int fd)
{
	int	count;
	char	*line;

	count = 0;
	line = get_next_line(fd);
	if (line == NULL || count_numbers(line) == 0)
		return (0);
	while(line != NULL)
	{
		free(line);
		count++;	
		line = get_next_line(fd);
		if (line != NULL && count_numbers(line) == 0)
			return (0);
	}
	return (count);
}

int **create_matrix(int fd, char *map)
{	
	int	**matrix;
	char *line;
	int	i;
	int	count;

	i = 0;
	count = count_rows(fd);
	matrix = (int **)malloc(sizeof(int *) * count);
	fd = close_and_read(fd, map);
    while (i < count)
    {
		line = get_next_line(fd);
		matrix[i] = build_row(line);
		free(line);
		i++;
    }
	return (matrix);
}