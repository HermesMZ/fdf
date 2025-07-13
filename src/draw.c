/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 02:12:56 by zoum              #+#    #+#             */
/*   Updated: 2025/07/13 05:05:43 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_mlx_data *data, int x, int y, int color)
{
	int	offset;

	if (x < 0 || x >= data->width || y < 0 || y >= data->height)
	{
		// ft_printf("DEBUG: Pixel rejeté: (%d, %d) hors limites (%d, %d)\n", x, y, data->width, data->height);
		return ;
	}
	offset = (data->img->line_len * y) + (x * (data->img->bits_per_pixel / 8));
	*((unsigned int *)(offset + data->img->addr)) = color;
}

void	move_draw(t_draw *draw, t_point *p1)
{
	int	err;

	err = 2 * draw->err;
	if (err > -draw->dy)
	{
		draw->err -= draw->dy;
		p1->px += draw->sx;
	}
	if (err < draw->dx)
	{
		draw->err += draw->dx;
		p1->py += draw->sy;
	}
}

void	draw_line(t_point *p1, t_point p2, t_mlx_data *data, int color)
{
	t_draw	draw;

	    // ft_printf("DEBUG: draw_line appelée de (px: %d, py: %d) vers (px: %d, py: %d)\n", p1->px, p1->py, p2.px, p2.py);
	draw.dx = abs(p2.px - p1->px);
	draw.dy = abs(p2.py - p1->py);
	if (p1->px < p2.px)
		draw.sx = 1;
	else
		draw.sx = -1;
	if (p1->py < p2.py)
		draw.sy = 1;
	else
		draw.sy = -1;
	draw.err = draw.dx - draw.dy;
	while (1)
	{
		my_mlx_pixel_put(data, p1->px, p1->py, color);
		if (p1->px == p2.px && p1->py == p2.py)
			break ;
		move_draw(&draw, p1);
	}
}


// --- TRACER LES LIGNES ---
// Cette partie sera ajoutée une fois que les points sont bien affichés.
// Elle nécessitera de calculer et projeter les points voisins
// puis d'appeler une fonction de tracé de ligne (Bresenham ou équivalent).
// Exemple (pseudocode):
// if (c < data->map->columns - 1) // Si pas le dernier de la ligne
// {
//     t_point point_right;
//     point_right.x = (double)(c + 1);
//     point_right.y = (double)l;
//     point_right.z = (double)data->map->array_map[l][c+1];
//     point_right = rotate_point(point_right, data);
//     point_right = project_iso(point_right, data);
//     draw_line(point.px, point.py, point_right.px, point_right.py,
		// data->img, 0x00FF00); // Vert
// }
// if (l < data->map->lines - 1) // Si pas le dernier de la colonne
// {
//     t_point point_down;
//     point_down.x = (double)c;
//     point_down.y = (double)(l + 1);
//     point_down.z = (double)data->map->array_map[l+1][c];
//     point_down = rotate_point(point_down, data);
//     point_down = project_iso(point_down, data);
//     draw_line(point.px, point.py, point_down.px, point_down.py,
		// data->img, 0x0000FF); // Bleu
// }
