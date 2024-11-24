
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
void	line_algorithm(int *x1, int *y1, int x2, int y2, mlx_image_t* img)
{
	int dx;
	int dy;
	int	pixel;

	dx = x2 - *x1;
	dy = y2 - *y1;
	pixel = (2 * dy) - dx;
	while (*x1 < x2)
	{
		mlx_put_pixel(img, *x1 , *y1, 0xFF0000FF);
		*x1 = *x1 + 1;
		if (pixel < 0)
			pixel = pixel + (2 * dy);
		else
		{
			pixel = pixel + (2 * dy) - (2 * dx);
			*y1 = *y1 + 1;
		}
	}
}
//void	vertical_draw()
int32_t	main(int arg, char **args)
{
	t_greedval gvals;
	int	**matrix;
	int	count;
	int	nmb_count;
	char *line;
	int fd;
	int	k;
	int	a;
	int	col_start_point;
	int	rsp;
	int	row_count;

    gvals.x = 1980/2;
	gvals.y = 0;
	gvals.i = 0;
    fd = open(args[1], O_RDONLY);
	if (arg > 3)
		return 0;
	matrix = create_matrix(fd, args[1]);
	fd = close_and_read(fd, args[1]);
	nmb_count = count_numbers(get_next_line(fd));
	printf("NUM OF COL : %d \n", nmb_count);
	count = count_rows(fd ) + 1;
	printf("NUM OF ROWS : %d \n", count);
	while (gvals.i < count)
	{
		gvals.j = 0;
		while (gvals.j < nmb_count)
		{
			printf("%d ", matrix[gvals.i][gvals.j]);
			gvals.j++;
		}
		free(matrix[gvals.i]);
		printf("\n");
		gvals.i++;
	}
	free(matrix);
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "42Balls", true);
	if (!mlx)
		return 0;
	mlx_image_t* img = mlx_new_image(mlx, 1980, 1020);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		return 0;

	row_count = 0;

	gvals.j = 0;
	while (gvals.j < nmb_count - 1)
	{
		k = 0;
		col_start_point = gvals.i;
		line_algorithm(&gvals.x, &gvals.y, gvals.x + 20 , gvals.y + 10, img);
		/*while (k <= 20)
		{
			mlx_put_pixel(img, gvals.x + gvals.i , gvals.y + a , 0xFF0000FF);
			mlx_put_pixel(img, gvals.x + col_start_point - k , gvals.y + a , 0xFF0000FF);
			gvals.i++;;
			k++;
			mlx_put_pixel(img, gvals.x + col_start_point - k , gvals.y + a + , 0xFF0000FF);
			mlx_put_pixel(img, gvals.x + gvals.i  , gvals.y + a , 0xFF0000FF);
			gvals.i++;;
			a++;
			k++;
		}*/
		gvals.j++;
	}
	while (row_count < count - 1)
	{
		gvals.j = 0;
		a = 0;
		gvals.i = 0;
		while (gvals.j < nmb_count - 1)
		{
			k = 0;
			col_start_point = gvals.i;
			while (k <= 20)
			{
				mlx_put_pixel(img, gvals.x + gvals.i , gvals.y + a , 0xFF0000FF);
				mlx_put_pixel(img, gvals.x + col_start_point - k , gvals.y + a , 0xFF0000FF);
				gvals.i++;;
				k++;
				mlx_put_pixel(img, gvals.x + col_start_point - k , gvals.y + a , 0xFF0000FF);
				mlx_put_pixel(img, gvals.x + gvals.i  , gvals.y + a , 0xFF0000FF);
				gvals.i++;;
				a++;
				k++;
			}
			gvals.j++;
		}
		gvals.x = gvals.x - 20;
		gvals.y = gvals.y + 10;
		row_count++;
	}
	// Register a hook and pass mlx as an optional param.
	// NOTE: Do this before calling mlx_loop!
	//mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	close(fd);
}
