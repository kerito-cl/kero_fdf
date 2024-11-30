/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 12:00:09 by mquero            #+#    #+#             */
/*   Updated: 2024/11/30 14:04:29 by mquero           ###   ########.fr       */
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
#define HEIGHT 1020/2
#define SCALE 20
#define HEIGHT_SCALE 20
#define ANGLE 0.523599

typedef struct s_gridval
{
	int row_count;
	int nmb_count;
	int	j;
    int i;
}		t_gridval;

typedef struct s_matrix
{
	unsigned int **colors;
	int **numbers;
}		t_matrix;

typedef struct s_coord
{
	double alpha;
	double beta;
	double gamma;
	int	z;
	int	dx;
	int	dy;
    int iso_x;
	int	iso_y;
    int dest_x;
	int	dest_y;
    int dest2_x;
	int	dest2_y;
	unsigned int	r1;
	unsigned int	b1;
	unsigned int	g1;
	unsigned int	r2;
	unsigned int	b2;
	unsigned int	g2;
	unsigned int	a;
	unsigned int	final_color;
}		t_coord;

void draw_map(mlx_image_t *img, int count, int nmb_count, t_matrix m);
void isometric_projection1(int i, int j, int z, t_coord *coord);
void isometric_projection2(int i, int j, int z, t_coord *coord);
void isometric_projection3(int i, int j, int z, t_coord *coord); 
void calcul_coord(t_gridval *gvals, t_coord *coord, t_matrix m);
void calcul_coord_dest(t_gridval *gvals, t_coord *coord, t_matrix m );
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
void	freecolors(unsigned int **m, int count);
void	freematrix(int **m, int count);
unsigned int **color_matrix(int fd, char *map);
void	set_color1(t_matrix m, t_coord *coord, int row, int col);
void	set_color2(t_matrix m, t_coord *coord, int row, int col);
void	putcolors(t_matrix *m, int count, int count_n);

#endif