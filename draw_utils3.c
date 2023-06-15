/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:48:54 by rleskine          #+#    #+#             */
/*   Updated: 2023/05/22 14:12:52 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

unsigned int	get_color(t_fdf *fdf, int x, int y)
{
	if (fdf->clrmode == 0 || fdf->clrmode == 1)
	{
		fdf->ln.rd = getxy(fdf, fdf->rot, (int [2]){x, y}, 1);
		if (fdf->clrmode == 0 && fdf->ln.rd == -1)
			return (0x00FFFFFF);
		else if (fdf->clrmode == 1 && fdf->ln.rd == -1)
			return (0x00000000);
		else
			return ((unsigned int)(fdf->ln.rd));
	}
	fdf->ln.rgb = 0x00FFFFFF;
	fdf->ln.rgb2 = 0x00FFFFFF;
	if (fdf->clrmode == 2)
		fdf->ln.rgb = 0;
	else
		fdf->ln.rgb2 = 0;
	fdf->ln.rd = 0 + (fdf->ln.rgb & 0xFF) - (fdf->ln.rgb2 & 0xFF);
	fdf->ln.rd = (fdf->ln.rd * getxy(fdf, fdf->rot, (int [2]){x, y}, 0) * 10)
		/ (fdf->map->max - fdf->map->min) / 10;
	return (fdf->ln.rgb2 + (fdf->ln.rd << 16) + (fdf->ln.rd << 8) + fdf->ln.rd);
}

void	put_pixel(t_fdf *fdf, int x, int y, unsigned int color)
{
	char	*dst;

	if (x > -1 && x < fdf->wx && y > -1 && y < fdf->wy)
	{
		dst = fdf->img.addr + (y * fdf->img.len + x * (fdf->img.bits_ppx / 8));
		*(unsigned int *)dst = color;
	}
}

void	rot_xy(t_fdf *fdf, int x, int y)
{
	x = x * 6 - (getxy(fdf, fdf->rot, NULL, 2) * 3) + 3;
	y = y * 6 - (getxy(fdf, fdf->rot, NULL, 3) * 3) + 3;
	fdf->rx = x * cos(fdf->rrad) - y * sin(fdf->rrad);
	fdf->ry = x * sin(fdf->rrad) + y * cos(fdf->rrad);
	fdf->rx = (fdf->rx + (getxy(fdf, fdf->rot, NULL, 2) * 3)) - 3;
	fdf->ry = (fdf->ry + (getxy(fdf, fdf->rot, NULL, 3) * 3)) - 3;
}
