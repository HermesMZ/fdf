/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:18:19 by mzimeris          #+#    #+#             */
/*   Updated: 2025/07/13 02:43:28 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	hard_values(t_mlx_data *data)
{
	data->width = 1000;
	data->height = 1000;
	data->map->array_map = NULL;
	data->map->columns = 0;
	data->map->lines = 0;
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	data->zoom = 20;
	data->offset_x = data->width / 2;
	data->offset_y = data->height / 2;
	data->angle_x = -0.5;
	data->angle_y = 0.0;
	data->angle_z = 0.5;
}

t_mlx_data	*init_data(void)
{
	t_mlx_data	*data;

	data = malloc(sizeof(t_mlx_data));
	if (!data)
		return (NULL);
	data->img = malloc(sizeof(t_my_img));
	if (!data->img)
		return (free(data), NULL);
	data->map = malloc(sizeof(t_map));
	if (!data->map)
	{
		free(data->img);
		free(data);
		return (NULL);
	}
	hard_values(data);
	return (data);
}
