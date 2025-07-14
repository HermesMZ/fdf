/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:59:59 by mzimeris          #+#    #+#             */
/*   Updated: 2025/07/14 16:43:20 by zoum             ###   ########.fr       */
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
		data->angle_x += 0.01;
	if (keysym == 106)
		data->angle_x -= 0.01;
	if (keysym == 105)
		data->angle_y += 0.01;
	if (keysym == 107)
		data->angle_y -= 0.01;
	if (keysym == 111)
		data->angle_z += 0.01;
	if (keysym == 108)
		data->angle_z -= 0.01;
}

static void	zoom_img(int keysym, t_mlx_data *data)
{
	if (keysym == 121)
		data->zoom -= 1;
	if (keysym == 104)
		data->zoom += 1;
	ft_printf("zoom : %d\n", data->zoom);
}

static void	translate_img(int keysym, t_mlx_data *data)
{
	if (keysym == 119)
		data->offset_y -= 8;
	if (keysym == 115)
		data->offset_y += 8;
	if (keysym == 97)
		data->offset_x -= 8;
	if (keysym == 100)
		data->offset_x += 8;
}

static void	depth_img(int keysym, t_mlx_data *data)
{
	if (keysym == 113)
		data->depth -= 1;
	if (keysym == 101)
		data->depth += 1;
	ft_printf("depth : %d\n", data->depth);
}

int	handle_input(int keysym, t_mlx_data *data)
{
	if (keysym == XK_Escape)
		end_display(data);
	if (keysym == 117 || keysym == 106 || keysym == 105 || keysym == 107
		|| keysym == 111 || keysym == 108)
		rotate_img(keysym, data);
	if (keysym == 121 || keysym == 104)
		zoom_img(keysym, data);
	if (keysym == 119 || keysym == 115 || keysym == 97 || keysym == 100)
		translate_img(keysym, data);
	if (keysym == 113 || keysym == 101)
		depth_img(keysym, data);
	if (keysym != XK_Escape)
	{
		draw_map(data);
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->img->img, 0, 0);
	}
	ft_printf("The %d key has been pressed\n\n", keysym);
	return (0);
}
