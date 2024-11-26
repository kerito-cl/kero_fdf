
#include "ft_fdf.h"
// Exit the program as failure.
/**
 * Main MLX handle, carries important data in regards to the program.
 * @param window The window itself.
 * @param context Abstracted opengl data.
 * @param width The width of the window.
 * @param height The height of the window.
 * @param delta_time The time difference between the previous frame and the current frame.
 */

void isometric_projection1(int i, int j, int z, t_coord *coord) {
    // Calculate isometric x and y using the formulas
	int	scale;
	double calc_x;
	double calc_y;
	double height_scale;

	scale = 60;
	height_scale = 10;
    calc_x = roundf((j - i) * scale * cos(0.72));
    calc_y = roundf(((i + j) * (scale/2) * sin(0.72)) - (z * height_scale));
	coord->iso_x = calc_x;
	coord->iso_y = calc_y;
}

void isometric_projection2(int i, int j, int z, t_coord *coord) {
    // Calculate isometric x and y using the formulas
	int	scale;
	double calc_x;
	double calc_y;
	double height_scale;

	scale = 60;
	height_scale = 10;
    calc_x = roundf((j - i) * scale * cos(0.72));
    calc_y = roundf(((i + j) * (scale/2) * sin(0.72)) - (z * height_scale));
	coord->dest_x = calc_x;
	coord->dest_y = calc_y;
}

void isometric_projection3(int i, int j, int z, t_coord *coord) {
    // Calculate isometric x and y using the formulas
	int	scale;
	double calc_x;
	double calc_y;
	double height_scale;

	scale = 60;
	height_scale = 10;
    calc_x = roundf((j - i) * scale * cos(0.72));
    calc_y = roundf(((i + j) * (scale/2) * sin(0.72)) - (z * height_scale));
	coord->dest2_x = calc_x;
	coord->dest2_y = calc_y;
}

void	line_algorithm(int x1, int y1, int x2, int y2, mlx_image_t* img)
{
	int dx;
	int dy;
	int	pixel;

	dx = abs(x2 - x1);
	dy = (y2 - y1);
	pixel = (2 * dy) - dx;
	while (x1 < x2 || x1 > x2)
	{
		mlx_put_pixel(img, x1 , y1, 0xFF0000FF);
		if (x1 < x2)
			x1 = x1 + 1;
		else
			x1 = x1 - 1;
		if (pixel < 0)
			pixel = pixel + (2 * dy);
		else
		{
			pixel = pixel + (2 * dy) - (2 * dx);
			if (y1 < y2)
				y1 = y1 + 1;
			else
				y1 = y1 - 1;
		}
	}
}

void	line_slope_bigger(int x1, int y1, int x2, int y2, mlx_image_t* img)
{
	int dx;
	int dy;
	int	pixel;

	dx = abs(x2 - x1);
	dy = abs(y2 - y1);
	pixel = (2 * dx) - dy;
	while (y1 < y2 || y1 > y2)
	{
		mlx_put_pixel(img, x1 , y1, 0xFF0000FF);
		if (y1 < y2)
			y1 = y1 + 1;
		else
			y1 = y1 - 1;
		if (pixel < 0)
			pixel = pixel + (2 * dx);
		else
		{
			pixel = pixel + (2 * dx) - (2 * dy);
			if (x1 < x2)
				x1 = x1 + 1;
			else
				x1 = x1 - 1;
		}
	}
}

/*void calcul_coord(t_gridval *gvals, t_coord *coord, int **matrix)
{

	gvals->z = matrix[gvals->row_count][gvals->j];
	isometric_projection1(gvals->row_count, gvals->j, gvals->z, coord);
	gvals->z = gvals->matrix[gvals->row_count][gvals->j + 1];
	isometric_projection2(gvals->row_count, gvals->j + 1, gvals->z, coord);
	coord->dx = abs(coord->iso_x - coord->dest_x);
	coord->dy = abs(coord->iso_y - coord->dest_y);
}*/
void draw_map(mlx_image_t *img, int count, int nmb_count, int **matrix)
{
	t_gridval gvals;
	t_coord coord;

    gvals.x = 2560/2;
	gvals.y = 1440/2;
	gvals.row_count = 0;
	while (gvals.row_count + 1 < count)
	{
		gvals.j = 0;
		while (gvals.j + 1 < nmb_count)
		{
			gvals.z = matrix[gvals.row_count][gvals.j];
            isometric_projection1(gvals.row_count, gvals.j, gvals.z, &coord);
			gvals.z = matrix[gvals.row_count][gvals.j + 1];
            isometric_projection2(gvals.row_count, gvals.j + 1, gvals.z, &coord);
			coord.dx = abs(coord.iso_x - coord.dest_x);
			coord.dy = abs(coord.iso_y - coord.dest_y);
			//calcul_coord(&gvals, &coord, matrix);
			if (coord.dx > coord.dy)
				line_algorithm(gvals.x + coord.iso_x, gvals.y + coord.iso_y, gvals.x + coord.dest_x , gvals.y + coord.dest_y, img);
			else
				line_slope_bigger(gvals.x + coord.iso_x, gvals.y + coord.iso_y, gvals.x + coord.dest_x , gvals.y + coord.dest_y, img);
			gvals.z = matrix[gvals.row_count + 1][gvals.j];
            isometric_projection3(gvals.row_count + 1, gvals.j, gvals.z, &coord);
			coord.dx = abs(coord.iso_x - coord.dest2_x);
			coord.dy = abs(coord.iso_y - coord.dest2_y);
			if (coord.dx > coord.dy)
				line_algorithm(gvals.x + coord.iso_x, gvals.y + coord.iso_y, gvals.x + coord.dest2_x , gvals.y + coord.dest2_y, img);
			else
				line_slope_bigger(gvals.x + coord.iso_x, gvals.y + coord.iso_y, gvals.x + coord.dest2_x , gvals.y + coord.dest2_y, img);
			gvals.j++;
		}
		gvals.row_count++;
	}
}
int32_t	main(int arg, char **args)
{
	int	count;
	int nmb_count;
	int fd;
	int **matrix;
	mlx_t* mlx;
	mlx_image_t* img;

	mlx = mlx_init(WIDTH, HEIGHT, "Kero FDF", true);
	img = mlx_new_image(mlx, 4096, 2160);
	if (!mlx)
		return 0;
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		return 0;
	mlx_set_setting(MLX_MAXIMIZED, true);
    fd = open(args[1], O_RDONLY);
	if (arg > 3)
		return 0;
	matrix = create_matrix(fd, args[1]);
	fd = close_and_read(fd, args[1]);
	nmb_count = count_numbers(get_next_line(fd));
	printf("NUM OF COL : %d \n", nmb_count);
	count = count_rows(fd) + 1;
	printf("NUM OF ROWS : %d \n", count);
	draw_map(img, count, nmb_count, matrix);
	// Register a hook and pass mlx as an optional param.
	// NOTE: Do this before calling mlx_loop!
	//mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	close(fd);
}
