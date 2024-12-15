/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 12:00:09 by mquero            #+#    #+#             */
/*   Updated: 2024/12/15 12:00:27 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FDF_H
# define FT_FDF_H

# include "MLX42/MLX42.h"
# include "gnl/get_next_line.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 1980
# define HEIGHT 1080

typedef struct s_matrix
{
	unsigned int	**colors;
	int				**numbers;
	int				total_rows;
	int				total_cols;

}					t_matrix;

typedef struct s_coord
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	unsigned int	**colors;
	int				**numbers;
	int				total_rows;
	int				total_cols;
	double			alpha;
	double			tetha;
	double			gamma;
	double			scale;
	double			height_scale;
	int				width;
	int				height;
	int				z;
	int				dx;
	int				dy;
	int				iso_x;
	int				iso_y;
	int				dest_x;
	int				dest_y;
	int				dest2_x;
	int				dest2_y;
	unsigned int	r1;
	unsigned int	b1;
	unsigned int	g1;
	unsigned int	r2;
	unsigned int	b2;
	unsigned int	g2;
	unsigned int	a;
	unsigned int	final_color;
	int				row_count;
	int				nmb_count;
	int				j;
	int				x_offset;
	int				y_offset;
	int				set_max;
	int				set_min;
	int				fd_folder;
}					t_coord;

void				draw_map(void *param);
void				isometric_projection1(int i, int j, t_coord *c);
void				isometric_projection2(int i, int j, t_coord *c);
void				isometric_projection3(int i, int j, t_coord *c);
void				calcul_coord(t_coord *c);
void				calcul_coord_dest(t_coord *c);
void				line_algorithm(t_coord c, int x2, int y2, mlx_image_t *img);
void				line_slope_bigger(t_coord c, int x2, int y2,
						mlx_image_t *img);
int					ft_isdigit(int i);
int					close_and_read(int fd, char *map);
int					count_numbers(char *line);
int					*build_row(char *line);
int					count_rows(int fd);
int					**create_matrix(int fd, char *map);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
char				**ft_split(char const *s, char c);
void				freesplit(char **strs);
void				freecolors(unsigned int **m, int count);
void				freematrix(int **m, int count);
unsigned int		**color_matrix(int fd, char *map, int cols);
void				set_color1(t_coord *c, int row, int col);
void				set_color2(t_coord *c, int row, int col);
void				putcolors(t_coord *m);
void				rotate_z(int *x, int *y, t_coord *c);
void				rotate_z(int *x, int *y, t_coord *c);
void				rotate_y(int *x, int *z, t_coord *c);
void				rotate_x(int *y, int *z, t_coord *c);
int					check_error(char *map);
void				free_all(t_coord *c);
void				throw_error(int flag);
int					check_if_fdf(char *str);
void				find_min_max(t_coord *c, int rows, int cols);
void				rescale_grid(t_coord *c, int rows, int cols);

#endif
