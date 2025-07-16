/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:20:24 by mzimeris          #+#    #+#             */
/*   Updated: 2025/07/16 18:24:28 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	close_gnl_fd(int fd)
{
	get_next_line(-1);
	close(fd);
}

void	free_map(int **tab)
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

void	print_map(t_mlx_data *data)
{
	int	l;
	int	c;

	ft_printf("lines %d, columns %d\n", data->map->lines, data->map->columns);
	l = 0;
	while (l < data->map->lines)
	{
		c = 0;
		while (c < data->map->columns)
		{
			ft_printf("%-2d ", data->map->array_map[l][c]);
			c++;
		}
		ft_printf("\n");
		l++;
	}
}

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
