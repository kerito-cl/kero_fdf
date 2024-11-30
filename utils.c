/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 13:40:49 by mquero            #+#    #+#             */
/*   Updated: 2024/11/30 14:13:29 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

int	ft_isdigit(int i)
{
	while ('0' <= i && i <= '9')
		return (1);
	return (0);
}

int	close_and_read(int fd, char *map)
{
	close(fd);
	fd = open(map, O_RDONLY);
	return (fd);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(src);
	if (size == 0)
		return (len);
	while (src[i] && i < (size - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len);
}

void	freematrix(int **m, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(m[i]);
		i++;
	}
	free(m);
}
void	freecolors(unsigned int **m, int count)
{
	int i;

	i = 0;
	while (i < count)
	{
		free(m[i]);
		i++;
	}
	free(m);
}