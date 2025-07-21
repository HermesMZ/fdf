/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:20:24 by mzimeris          #+#    #+#             */
/*   Updated: 2025/07/21 15:55:30 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	close_gnl_fd(int fd)
{
	get_next_line(-1);
	close(fd);
}

void	free_map(t_point **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	end_display(t_mlx_data *data)
{
	if (data->map)
	{
		free_map(data->map->points);
		free(data->map);
	}
	if (data->img && data->img->img)
	{
		mlx_destroy_image(data->mlx_ptr, data->img->img);
		free(data->img);
	}
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	if (data != NULL)
		free(data);
	exit(0);
	return (0);
}
