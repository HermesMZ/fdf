/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:44:24 by mzimeris          #+#    #+#             */
/*   Updated: 2025/07/23 13:40:44 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	debug_palette(t_mlx_data *data)
{
	int	i;

	i = 0;
	while (i < data->palette.len)
	{
		ft_printf("t %d, r %d, g %d, b %d = %d\n",
			data->palette.colors[i].t,
			data->palette.colors[i].r,
			data->palette.colors[i].g,
			data->palette.colors[i].b,
			data->palette.colors[i].color);
		i++;
	}
}

void	debug_print_map(t_mlx_data *data)
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
			ft_printf("%4d,%d ", (int)data->map->points[l][c].z,
				data->map->points[l][c].color.color);
			c++;
		}
		ft_printf("\n");
		l++;
	}
}
