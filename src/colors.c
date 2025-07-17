/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:33:15 by zoum              #+#    #+#             */
/*   Updated: 2025/07/17 18:36:29 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// int interpolate_color(int c1, int c2, double ratio)
// {
//     int r1 = (c1 >> 16) & 0xFF;
//     int g1 = (c1 >> 8) & 0xFF;
//     int b1 = c1 & 0xFF;

//     int r2 = (c2 >> 16) & 0xFF;
//     int g2 = (c2 >> 8) & 0xFF;
//     int b2 = c2 & 0xFF;

//     int r_interp = (int)(r1 + (r2 - r1) * ratio);
//     int g_interp = (int)(g1 + (g2 - g1) * ratio);
//     int b_interp = (int)(b1 + (b2 - b1) * ratio);

//     return (r_interp << 16) | (g_interp << 8) | b_interp;
// }


int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	extract_rgb(t_col *col, int c)
{
	col->color = c;
	col->t = (col->color >> 24) & 0xFF;
	col->r = (col->color >> 16) & 0xFF;
	col->g = (col->color >> 8) & 0xFF;
	col->b = (col->color & 0xFF);
}

int	interpolate_color(int c1, int c2, double ratio)
{
	t_col	col1;
	t_col	col2;
	t_col	inter;

	// printf("c1 %d c2 %d\n", c1, c2);
	extract_rgb(&col1, c1);
	extract_rgb(&col2, c2);
	inter.r = (col1.r + (col2.r - col1.r) * ratio);
	inter.g = (col1.g + (col2.g - col1.g) * ratio);
	inter.b = (col1.b + (col2.b - col1.b) * ratio);
	inter.t = (col1.t + (col2.t - col1.t) * ratio);
	// printf("%d %d %d %d\n", inter.r, inter.g, inter.b, inter.t);
	return (inter.t << 24 | inter.r << 16 | inter.g << 8 | inter.b);
}
