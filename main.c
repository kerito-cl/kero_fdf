
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

int32_t	main(int arg, char **args)
{
	int	i = 0;
	int j = 0;
	int fd;
	int	**matrix;
	int	count;
	int	nmb_count;
	char *line;

    fd = open(args[1], O_RDONLY);
	if (arg > 3)
		return 0;
	matrix = create_matrix(fd, args[1]);
	fd = close_and_read(fd, args[1]);
	nmb_count = count_numbers(get_next_line(fd));
	printf("NUM OF COL : %d \n", nmb_count);
	count = count_rows(fd ) + 1;
	printf("NUM OF ROWS : %d \n", count);
	while (i < count)
	{
		j = 0;
		while (j < nmb_count)
		{
			printf("%d ", matrix[i][j]);
			j++;
		}
		free(matrix[i]);
		printf("\n");
		i++;
	}
	free(matrix);
	
	

	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "42Balls", true);
	if (!mlx)
		return 0;
	mlx_image_t* img = mlx_new_image(mlx, 1980, 1020);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		return 0;
	i = 1980 / 2;
	j = 0;
	int x = 1040/2;
	while (j < nmb_count - 1)
	{
		mlx_put_pixel(img, i , x, 0xFF0000FF);
		i = i + 20;
		x = x + 10;
		j++;
	}
	j = 0;
	while (j < count - 1)
	{
		mlx_put_pixel(img, i , x, 0xFF0000FF);
		i = i - 20;
		x = x + 10;
		j++;
	}
	j = 0;
	i = 1980 / 2;
	x = 1040 /2;
	while (j < count - 1)
	{
		mlx_put_pixel(img, i , x, 0xFF0000FF);
		i = i - 20;
		x = x + 10;
		j++;
	}
	j = 0;
	while (j < nmb_count - 1)
	{
		mlx_put_pixel(img, i , x, 0xFF0000FF);
		i = i + 20;
		x = x + 10;
		j++;
	}
	mlx_put_pixel(img, i , x, 0xFF0000FF);
	// Register a hook and pass mlx as an optional param.
	// NOTE: Do this before calling mlx_loop!
	//mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	close(fd);
}
