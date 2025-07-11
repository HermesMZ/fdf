/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:59:59 by mzimeris          #+#    #+#             */
/*   Updated: 2025/07/12 00:22:07 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	end_display(t_mlx_data *data)
{
	free_map(data->map->array_map);
	data->map->array_map = NULL;
	free(data->map);
	data->map = NULL;
	mlx_destroy_image(data->mlx_ptr, data->img->img);
	data->img->img = NULL;
	free(data->img);
	data->img = NULL;
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	data->win_ptr = NULL;
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	free(data);
	exit(0);
}

int	handle_input(int keysym, t_mlx_data *data)
{
	if (keysym == XK_Escape)
		end_display(data);
	ft_printf("The %d key has been pressed\n\n", keysym);
	return (0);
}
