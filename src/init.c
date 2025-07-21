/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:18:19 by mzimeris          #+#    #+#             */
/*   Updated: 2025/07/21 21:41:05 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	hard_values(t_mlx_data *data)
{
	data->width = 1000;
	data->height = 500;
	data->map->points = NULL;
	data->map->columns = 0;
	data->map->lines = 0;
	data->map->min_z = 2147483647;
	data->map->max_z = -2147483648;
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	data->zoom = 1.0;
	data->offset_x = 0;
	data->offset_y = 0;
	data->angle_x = 0.2860;
	data->angle_y = 0.0060;
	data->angle_z = 0.5410;
	data->depth = 1.0;
	data->keys = (t_keys){0};
	data->keys.first_draw = 1;
	data->colorized = 0;
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
	data->img->img = NULL;
	data->map = malloc(sizeof(t_map));
	if (!data->map)
	{
		free(data->img);
		return (free(data), NULL);
	}
	hard_values(data);
	return (data);
}

t_point	**create_map(int lines, int col)
{
	t_point	**points;
	int		i;

	points = malloc(sizeof(t_point *) * (lines + 1));
	if (!points)
		return (NULL);
	i = 0;
	points[lines] = NULL;
	while (i < lines)
	{
		points[i] = malloc(sizeof(t_point) * (col + 1));
		if (!points[i])
			return (free_map(points), NULL);
		ft_memset(points[i], 0, sizeof(t_point) * col);
		i++;
	}
	return (points);
}
