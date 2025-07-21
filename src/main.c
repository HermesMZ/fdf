/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 17:36:48 by zoum              #+#    #+#             */
/*   Updated: 2025/07/21 21:35:17 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char *argv[])
{
	t_mlx_data	*data;

	if (argc != 2)
		return (ft_putstr_fd("Error: Select one map\n", 2), 1);
	data = init_data();
	if (!data)
		return (ft_putstr_fd("Error: Failed data init\n", 2), 1);
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return (ft_putstr_fd("Error: Failed mlx_ptr init\n", 2), 1);
	if (check_extract_map(data, argv[1]) != 0)
		return (ft_putstr_fd("Error: Invalid map\n", 2), 1);
	setup_view(data);
	if (launch(data) != 0)
	{
		end_display(data);
		return (ft_putstr_fd("Error: Failed to launch FdF window\n", 2), 1);
	}
	draw_map(data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, key_press, data);
	mlx_hook(data->win_ptr, KeyRelease, KeyReleaseMask, key_release, data);
	mlx_hook(data->win_ptr, 17, 0, end_display, data);
	mlx_loop_hook(data->mlx_ptr, main_loop_update, data);
	mlx_loop(data->mlx_ptr);
	return (0);
}
