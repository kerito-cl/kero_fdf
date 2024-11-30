/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:33:57 by mquero            #+#    #+#             */
/*   Updated: 2024/11/30 13:52:46 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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

void my_keyhook(mlx_key_data_t keydata, void* param)
{
	// If we PRESS the 'J' key, print "Hello".
	if (keydata.key == MLX_KEY_J && keydata.action == MLX_REPEAT)
		;

	// If we RELEASE the 'K' key, print "World".
	if (keydata.key == MLX_KEY_K && keydata.action == MLX_REPEAT)
		puts("World");

	// If we HOLD the 'L' key, print "!".
	if (keydata.key == MLX_KEY_L && keydata.action == MLX_REPEAT)
		puts("!");
}
int32_t	main(int arg, char **args)
{
	int	count;
	int nmb_count;
	int fd;
	t_matrix m;
	mlx_t* mlx;
	mlx_image_t* img;

	if (arg > 2)
		return 0;
	mlx = mlx_init(WIDTH, HEIGHT, "Kero FDF", true);
	img = mlx_new_image(mlx, 4096, 2160);
	if (!mlx)
		return 0;
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		return 0;
	//mlx_set_setting(MLX_MAXIMIZED, true);
    fd = open(args[1], O_RDONLY);
	m.numbers = create_matrix(fd, args[1]);
	fd = close_and_read(fd, args[1]);
	m.colors = color_matrix(fd, args[1]);
	fd = close_and_read(fd, args[1]);
	nmb_count = count_numbers(get_next_line(fd));
	printf("NUM OF COL : %d \n", nmb_count);
	count = count_rows(fd) + 1;
	printf("NUM OF ROWS : %d \n", count);
	putcolors(&m,count, nmb_count);

	draw_map(img, count, nmb_count, m);



	mlx_key_hook(mlx, &my_keyhook, NULL);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	freecolors(m.colors, count);
	freematrix(m.numbers, count);
	close(fd);
}
