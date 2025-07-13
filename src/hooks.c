/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:59:59 by mzimeris          #+#    #+#             */
/*   Updated: 2025/07/13 18:07:33 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	end_display(t_mlx_data *data)
{
	if (data->map)
	{
		free_map(data->map->array_map);
		free(data->map);
	}
	if (data->img && data->img->img)
	{
		mlx_destroy_image(data->mlx_ptr, data->img->img);
		free(data->img);
	}
	if (data->win_ptr != NULL)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	}
	if (data->mlx_ptr != NULL)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	if (data != NULL)
		free(data);
	exit(0);
	return (0);
}

static void	rotate_img(int keysym, t_mlx_data *data)
{
	if (keysym == 117)
		data->angle_x += 0.1;
	if (keysym == 106)
		data->angle_x -= 0.1;
	if (keysym == 105)
		data->angle_y += 0.1;
	if (keysym == 107)
		data->angle_y -= 0.1;
	if (keysym == 111)
		data->angle_z += 0.1;
	if (keysym == 108)
		data->angle_z -= 0.1;
}

int	handle_input(int keysym, t_mlx_data *data)
{
	if (keysym == XK_Escape)
		end_display(data);
	if (keysym == 117 || keysym == 106 || keysym == 105 || keysym == 107
		|| keysym == 111 || keysym == 108)
		rotate_img(keysym, data);
	if (keysym != XK_Escape)
	{
		draw_map(data);
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->img->img, 0, 0);
	}
	ft_printf("The %d key has been pressed\n\n", keysym);
	return (0);
}
