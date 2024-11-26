/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 12:00:09 by mquero            #+#    #+#             */
/*   Updated: 2024/11/26 10:30:20 by mquero           ###   ########.fr       */
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

typedef struct s_gridval
{
	int **matrix;
	int row_count;
	int nmb_count;
	int	x;
	int	y;
    int z;
	int	j;
    int i;

}		t_gridval;

typedef struct s_coord
{
	int	dx;
	int	dy;
    int iso_x;
	int	iso_y;
    int dest_x;
	int	dest_y;
    int dest2_x;
	int	dest2_y;
}		t_coord;

void isometric_projection(int row_count, int j, int z, int *iso_x, int *iso_y);
void	line_algorithm(int x1, int y1, int x2, int y2, mlx_image_t* img);
void	line_slope_bigger(int x1, int y1, int x2, int y2, mlx_image_t* img);
int	ft_isdigit(int i);
int	close_and_read(int fd, char *map);
int	count_numbers(char *line);
int	*build_row(char *line);
int count_rows(int fd);
int **create_matrix(int fd, char *map);


#endif