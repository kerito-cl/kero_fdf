
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <stdbool.h>
#include "MLX42/MLX42.h"
#include "gnl/get_next_line.h"
#define WIDTH 256
#define HEIGHT 256

// Exit the program as failure.
/**
 * Main MLX handle, carries important data in regards to the program.
 * @param window The window itself.
 * @param context Abstracted opengl data.
 * @param width The width of the window.
 * @param height The height of the window.
 * @param delta_time The time difference between the previous frame and the current frame.
 */

int	close_and_read(int fd, char *map)
{
	close(fd);
    fd = open(map, O_RDONLY);
	return (fd);
}
int	count_numbers(char *line)
{
	int i;
	int	count;

	i = 0;
	count = 0;
	if (line[i] < '0' || line[i] > '9')
		return (0);
	while (line[i])
	{
		while ((line[i] >= '0' && line[i] <= '9') || line[i] == ' ')
		{
			if(line[i] == ' ' && line[i + 1] == ' ')
				return (0);
			i++;
			if (line[i] == ' ')
				count++;
		}
		if (line[i] != '\n')
			return (0);
		count++;
		i++;
	}
	return	(count);
}
// Print the window width and height.
int	*build_row(char *line)
{
	int	i;
	int	j;
	int	*row;
	int	count;
	int	hold;

	count = count_numbers(line);
	row = (int *)malloc(count * sizeof(int));
	if (row == NULL || count == 0)
	{
		free(row);
		return (NULL);
	}
	j = 0;
	i = 0;
	while (line[i])
	{
	hold = 0;
		if (line[i] == ' ')
		{
			row[j] = ft_atoi(line + hold);
			hold = i + 1;
			j++;
		}
		i++;
	}
	row[j] = ft_atoi(line + hold);
	return (row);
}

int count_rows(int fd)
{
	int	count;
	char	*line;

	count = 0;
	line = get_next_line(fd);
	if (line == NULL || count_numbers(line) == 0)
		return (0);
	while(line != NULL)
	{
		free(line);
		count++;	
		line = get_next_line(fd);
		if (line != NULL && count_numbers(line) == 0)
			return (0);
	}
	return (count);
}

int **create_matrix(int fd, char *map)
{	
	int	**matrix;
	char *line;
	int	i;
	int	count;

	i = 0;
	count = count_rows(fd);
	matrix = (int **)malloc(sizeof(int *) * count);
	fd = close_and_read(fd, map);
    while (i < count)
    {
		line = get_next_line(fd);
		matrix[i] = build_row(line);
		free(line);
		i++;
    }
	return (matrix);
}

int32_t	main(int arg, char **args)
{
	int	i = 0;
	int j = 0;
	int fd;
	int	**matrix;
	int	count;

    fd = open(args[1], O_RDONLY);
	if (arg > 3)
		return 0;
	matrix = create_matrix(fd, args[1]);
	fd = close_and_read(fd, args[1]);
	count = count_rows(fd);
	while (i < count)
	{
		j = 0;
		while (j < count)
		{
			printf("%d ", matrix[i][j]);
			j++;
		}
		free(matrix[i]);
		printf("\n");
		i++;
	}
	free(matrix);
	
	
	//mlx_set_setting(MLX_MAXIMIZED, true);
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "42Balls", true);
	if (!mlx)
		return 0;
	// Create and display the image.
	mlx_image_t* img = mlx_new_image(mlx, 256, 256);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		return 0;
	// Even after the image is being displayed, we can still modify the buffer.
	while (i < 256)
	{
		mlx_put_pixel(img, i, 0, 0xFF0000FF);
		i++;
	}
	// Register a hook and pass mlx as an optional param.
	// NOTE: Do this before calling mlx_loop!
	//mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
