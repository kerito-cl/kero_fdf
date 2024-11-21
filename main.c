
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "MLX42/MLX42.h"
#include "gnl/get_next_line.h"
#define WIDTH 1256
#define HEIGHT 1256

// Exit the program as failure.
/**
 * Main MLX handle, carries important data in regards to the program.
 * @param window The window itself.
 * @param context Abstracted opengl data.
 * @param width The width of the window.
 * @param height The height of the window.
 * @param delta_time The time difference between the previous frame and the current frame.
 */

// Print the window width and height.
static void ft_hook(void* param)
{
	const mlx_t* mlx = param;

	printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
}
int 
int32_t	main(int arg, char **args)
{
	int	i = 5;
	int fd;
	char *line;
	int	grid[][];

    fd = open(args[1], O_RDONLY);
	if (arg > 3)
		return 0;
	line = get_next_line(fd);
	printf("%s", line);
	
	
	mlx_set_setting(MLX_MAXIMIZED, true);
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "42Balls", true);
	if (!mlx)
		return 0;

	/* Do stuff */


	// Create and display the image.
	mlx_image_t* img = mlx_new_image(mlx, 1000, 1000);
	if (!img || (mlx_image_to_window(mlx, img, 100, 100) < 0))
		return 0;

	// Even after the image is being displayed, we can still modify the buffer.
	while (i < 900)
	{
		mlx_put_pixel(img, i, 100, 0xFF0000FF);
		i++;
	}

	// Register a hook and pass mlx as an optional param.
	// NOTE: Do this before calling mlx_loop!
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
