/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:33:15 by zoum              #+#    #+#             */
/*   Updated: 2025/07/16 23:06:44 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int interpolate_color(int c1, int c2, double ratio)
{
    int r1 = (c1 >> 16) & 0xFF;
    int g1 = (c1 >> 8) & 0xFF;
    int b1 = c1 & 0xFF;

    int r2 = (c2 >> 16) & 0xFF;
    int g2 = (c2 >> 8) & 0xFF;
    int b2 = c2 & 0xFF;

    int r_interp = (int)(r1 + (r2 - r1) * ratio);
    int g_interp = (int)(g1 + (g2 - g1) * ratio);
    int b_interp = (int)(b1 + (b2 - b1) * ratio);

    return (r_interp << 16) | (g_interp << 8) | b_interp;
}