/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:59:59 by mzimeris          #+#    #+#             */
/*   Updated: 2025/07/10 16:36:04 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	end_display(t_mlx_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img.img);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(1);
}

int	handle_input(int keysym, t_mlx_data *data)
{
	if (keysym == XK_Escape)
		end_display(data);
	ft_printf("The %d key has been pressed\n\n", keysym);
	return (0);
}
