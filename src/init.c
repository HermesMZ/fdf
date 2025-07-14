/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:18:19 by mzimeris          #+#    #+#             */
/*   Updated: 2025/07/14 16:08:01 by zoum             ###   ########.fr       */
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
	data->zoom = 1;
	data->offset_x = 0;
	data->offset_y = 0;
	data->angle_x = -0.615;
	data->angle_y = 0.0;
	data->angle_z = 0.785;
	data->depth = 3;
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

int	**create_map(int lines, int col)
{
	int	**tab;
	int	i;

	tab = malloc(sizeof(int *) * (lines + 1));
	if (!tab)
		return (NULL);
	i = 0;
	tab[lines] = NULL;
	while (i < lines)
	{
		tab[i] = malloc(sizeof(int) * (col + 1));
		if (!tab[i])
			return (free_map(tab), NULL);
		ft_memset(tab[i], 0, sizeof(int) * col);
		i++;
	}
	return (tab);
}
