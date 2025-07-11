/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:18:19 by mzimeris          #+#    #+#             */
/*   Updated: 2025/07/11 15:58:07 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_mlx_data	*init_data(void)
{
	t_mlx_data	*data;

	data = malloc(sizeof(t_mlx_data));
	if (!data)
		return (NULL);
	data->img = malloc(sizeof(t_img));
	if (!data->img)
		return (free(data), NULL);
	data->map = malloc(sizeof(t_map));
	if (!data->map)
	{
		free(data->img);
		free(data);
		return (NULL);
	}
	data->map->array_map = NULL;
	data->map->columns = 0;
	data->map->lines = 0;
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	return (data);
}
