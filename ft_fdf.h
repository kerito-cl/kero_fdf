/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 12:00:09 by mquero            #+#    #+#             */
/*   Updated: 2024/11/23 13:41:07 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FDF_H
# define FT_FDF_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <stdbool.h>
#include "MLX42/MLX42.h"
#include "gnl/get_next_line.h"

#define WIDTH 1980
#define HEIGHT 1020

int	ft_isdigit(int i);
int	close_and_read(int fd, char *map);
int	count_numbers(char *line);
int	*build_row(char *line);
int count_rows(int fd);
int **create_matrix(int fd, char *map);


#endif