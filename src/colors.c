/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:33:15 by zoum              #+#    #+#             */
/*   Updated: 2025/07/21 16:11:08 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	extract_rgb(t_col *col, int c)
{
	col->color = c;
	col->t = (col->color >> 24) & 0xFF;
	col->r = (col->color >> 16) & 0xFF;
	col->g = (col->color >> 8) & 0xFF;
	col->b = (col->color & 0xFF);
}

int	interpolate_color(t_col c1, t_col c2, double ratio)
{
	t_col	inter;

	inter.r = (c1.r + (c2.r - c1.r) * ratio);
	inter.g = (c1.g + (c2.g - c1.g) * ratio);
	inter.b = (c1.b + (c2.b - c1.b) * ratio);
	inter.t = (c1.t + (c2.t - c1.t) * ratio);
	return (inter.t << 24 | inter.r << 16 | inter.g << 8 | inter.b);
}
