/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 12:00:09 by mquero            #+#    #+#             */
/*   Updated: 2024/11/26 22:07:01 by mquero           ###   ########.fr       */
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
#define SCALE 4
#define HEIGHT_SCALE 2
#define ANGLE 0.523599

typedef struct s_gridval
{
	int **matrix;
	int row_count;
	int nmb_count;
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
	int	color;
}		t_coord;

void draw_map(mlx_image_t *img, int count, int nmb_count, int **matrix);
void isometric_projection1(int i, int j, int z, t_coord *coord);
void isometric_projection2(int i, int j, int z, t_coord *coord);
void isometric_projection3(int i, int j, int z, t_coord *coord); 
void calcul_coord(t_gridval *gvals, t_coord *coord, int **matrix);
void calcul_coord_dest(t_gridval *gvals, t_coord *coord, int **matrix);
void	line_algorithm(t_coord coord, int x2, int y2, mlx_image_t* img);
void	line_slope_bigger(t_coord coord, int x2, int y2, mlx_image_t* img);
int	ft_isdigit(int i);
int	close_and_read(int fd, char *map);
int	count_numbers(char *line);
int	*build_row(char *line);
int count_rows(int fd);
int **create_matrix(int fd, char *map);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	**ft_split(char const *s, char c);
void	freesplit(char **strs);


#endif