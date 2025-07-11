/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:20:24 by mzimeris          #+#    #+#             */
/*   Updated: 2025/07/11 14:49:59 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_map(t_mlx_data *data)
{
	int	l;
	int	c;

	l = 0;
	while (l < data->map->lines)
	{
		c = 0;
		while (c < data->map->columns)
		{
			ft_printf("%d ", data->map->array_map[l][c]);
			c++;
		}
		ft_printf("\n");
		l++;
	}
}
