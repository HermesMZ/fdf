/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:07:09 by mzimeris          #+#    #+#             */
/*   Updated: 2025/07/13 18:49:01 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//matrices

#include "fdf.h"

int	launch(t_mlx_data *data)
{
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->width, data->height,
			"MY WORLD !");
	if (data->win_ptr == NULL)
	{
		mlx_destroy_display(data->mlx_ptr);
		return (1);
	}
	data->img->img = mlx_new_image(data->mlx_ptr, data->width, data->height);
	data->img->addr = mlx_get_data_addr(data->img->img,
			&data->img->bits_per_pixel, &data->img->line_len,
			&data->img->endian);
	draw_map(data);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_mlx_data	*data;

	if (argc != 2)
		return (ft_putstr_fd("Error: Select a map\n", 2), 1);
	data = init_data();
	if (!data)
		return (ft_putstr_fd("Error: Failed data init\n", 2), 1);
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return (ft_putstr_fd("Error: Failed mlx_ptr init\n", 2), 1);
	if (check_extract_map(data, argv[1]) != 0)
		return (ft_putstr_fd("Error: Invalid map\n", 2), 1);
	print_map(data);
	setup_view(data);
	if (launch(data) != 0)
	{
		end_display(data);
		return (ft_putstr_fd("Error: Failed to launch FdF window\n", 2), 1);
	}
	mlx_key_hook(data->win_ptr, handle_input, data);
	mlx_hook(data->win_ptr, 17, 0, end_display, data);
	mlx_loop(data->mlx_ptr);
	return (0);
}
