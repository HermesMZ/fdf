/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_view_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 18:39:57 by zoum              #+#    #+#             */
/*   Updated: 2025/07/13 18:46:41 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	update_bounds(t_point p_transformed, t_projected_bounds *bounds)
{
	if (!bounds->first_point_processed)
	{
		bounds->min_x = p_transformed.px;
		bounds->max_x = p_transformed.px;
		bounds->min_y = p_transformed.py;
		bounds->max_y = p_transformed.py;
		bounds->first_point_processed = 1;
	}
	else
	{
		if (p_transformed.px < bounds->min_x)
			bounds->min_x = p_transformed.px;
		else if (p_transformed.px > bounds->max_x)
			bounds->max_x = p_transformed.px;

		if (p_transformed.py < bounds->min_y)
			bounds->min_y = p_transformed.py;
		else if (p_transformed.py > bounds->max_y)
			bounds->max_y = p_transformed.py;
	}
}

void	find_projected_minmax(t_mlx_data *data, t_projected_bounds *bounds)
{
	int					l;
	int					c;
	t_point				p_original;
	t_point				p_transformed;

	bounds->first_point_processed = 0;
	l = 0;
	while (l < data->map->lines)
	{
		c = 0;
		while (c < data->map->columns)
		{
			p_original.x = (double)c;
			p_original.y = (double)l;
			p_original.z = (double)data->map->array_map[l][c];
			p_transformed = rotate(data, p_original);
			p_transformed = project(data, p_transformed);
			update_bounds(p_transformed, bounds);
			c++;
		}
		l++;
	}
}
