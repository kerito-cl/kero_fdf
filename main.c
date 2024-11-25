
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

void isometric_projection(int i, int j, int z, int *iso_x, int *iso_y) {
    // Calculate isometric x and y using the formulas
	int	scale = 20;
	double calc_x;
	double calc_y;
	double height_scale;

	height_scale = 4.0;
    calc_x = roundf((j - i) * scale * cos(0.52));
    calc_y = roundf(((i + j) * scale * sin(0.52)) - (z * height_scale));
	*iso_x = calc_x;
	*iso_y = calc_y;
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
int32_t	main(int arg, char **args)
{
	t_greedval gvals;
	int	**matrix;
	int	count;
	int	nmb_count;
	char *line;
	int fd;
	int	row_count;
	int	dy;
	int	dx;
    int iso_x, iso_y;
    int dest_x, dest_y;
    int dest2_x, dest2_y;

	mlx_set_setting(MLX_MAXIMIZED, true);
    gvals.x = 1980/2;
	gvals.y = 1020/4;
	gvals.i = 0;
    	fd = open(args[1], O_RDONLY);
	if (arg > 3)
		return 0;
	matrix = create_matrix(fd, args[1]);
	fd = close_and_read(fd, args[1]);
	nmb_count = count_numbers(get_next_line(fd));
	printf("NUM OF COL : %d \n", nmb_count);
	count = count_rows(fd) + 1;
	printf("NUM OF ROWS : %d \n", count);
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "Kero FDF", true);
	if (!mlx)
		return 0;
	mlx_image_t* img = mlx_new_image(mlx, 1980, 1020);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		return 0;

	row_count = 0;
	while (row_count + 1 < count)
	{
		gvals.j = 0;
		while (gvals.j + 1 < nmb_count)
		{
			gvals.z = matrix[row_count][gvals.j];
            isometric_projection(row_count, gvals.j, gvals.z, &iso_x, &iso_y);
            printf("Isometric Coordinates (x: %d, y: %d) with height %d\n",  iso_x, iso_y, gvals.z);
			gvals.z = matrix[row_count][gvals.j + 1];
            isometric_projection(row_count, gvals.j + 1, gvals.z, &dest_x, &dest_y);
            printf("Destination Coordinates (x: %d, y: %d) with height %d\n",  dest_x, dest_y, gvals.z);
			dx = abs(iso_x - dest_x);
			dy = abs(iso_y - dest_y);
			if (dx > dy)
				line_algorithm(gvals.x + iso_x, gvals.y + iso_y, gvals.x + dest_x , gvals.y + dest_y, img);
			else
				line_slope_bigger(gvals.x + iso_x, gvals.y + iso_y, gvals.x + dest_x , gvals.y + dest_y, img);

			gvals.z = matrix[row_count + 1][gvals.j];
            isometric_projection(row_count + 1, gvals.j, gvals.z, &dest2_x, &dest2_y);
            printf("Second Destination Coordinates (x: %d, y: %d) with height %d\n",  dest2_x, dest2_y, gvals.z);
			dx = abs(iso_x - dest2_x);
			dy = abs(iso_y - dest2_y);
			if (dx > dy)
				line_algorithm(gvals.x + iso_x, gvals.y + iso_y, gvals.x + dest2_x , gvals.y + dest2_y, img);
			else
				line_slope_bigger(gvals.x + iso_x, gvals.y + iso_y, gvals.x + dest2_x , gvals.y + dest2_y, img);
			gvals.j++;
		}
		row_count++;
	}
	// Register a hook and pass mlx as an optional param.
	// NOTE: Do this before calling mlx_loop!
	//mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	close(fd);
}
