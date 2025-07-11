/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:07:09 by mzimeris          #+#    #+#             */
/*   Updated: 2025/07/11 15:53:53 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define MLX_ERROR       1
#define WINDOW_WIDTH    1000
#define WINDOW_HEIGHT   1000

void	my_mlx_pixel_put(t_my_img *img, int x, int y, int color)
{
	int	offset;

	offset = (img->line_len * y) + (x * (img->bits_per_pixel / 8));
	*((unsigned int *)(offset + img->addr)) = color;
}

int	launch(t_mlx_data *data)
{
	data->win_ptr = mlx_new_window(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT,
			"MY WORLD !");
	if (data->win_ptr == NULL)
	{
		mlx_destroy_display(data->mlx_ptr);
		return (MLX_ERROR);
	}
	data->img->img = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->img->addr = mlx_get_data_addr(data->img->img,
			&data->img->bits_per_pixel, &data->img->line_len,
			&data->img->endian);
	my_mlx_pixel_put(data->img, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img->img, 0, 0);
	return (0);
}

int	main(int argc, char *argv[])
{
	int			fd;
	t_mlx_data	*data;

	data = init_data();
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return (MLX_ERROR);
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			return (ft_putstr_fd("Error: Can't Open File\n", 2), 1);
		if (check_extract_map(data, fd))
			return (ft_putstr_fd("Error: Invalid map\n", 2), 2);
	}
	launch(data);
	mlx_key_hook(data->win_ptr, handle_input, data);
	mlx_hook(data->win_ptr, 17, 0, end_display, data);
	mlx_loop(data->mlx_ptr);
}
