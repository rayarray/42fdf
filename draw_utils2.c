/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:29:47 by rleskine          #+#    #+#             */
/*   Updated: 2023/05/22 16:08:28 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	chk_vposs(t_fdf *fdf, double wxy[4])
{
	if ((wxy[0] < 0 && wxy[2] < 0) || (wxy[0] > fdf->wx && wxy[2] > fdf->wx))
		return (0);
	if ((wxy[1] < 0 && wxy[2] < 0) || (wxy[1] > fdf->wy && wxy[3] > fdf->wy))
		return (0);
	return (1);
}

double	get_wxy(t_fdf *fdf, int x, int y, int dim)
{
	double	xy;

	rot_xy(fdf, x, y);
	if (dim == 0)
	{
		xy = fdf->x0 + (fdf->rx / 6) * (fdf->xlen / 10);
		xy += (fdf->wx - (fdf->vx / 10)) / 2 + fdf->xyadj[0];
	}
	else
	{
		xy = fdf->y0 + (fdf->ry / 6) * (fdf->ylen / 10);
		xy = (xy - (fdf->wy / 2)) * sin(fdf->prad) + (fdf->wy / 2);
		xy += (fdf->wy - (fdf->vy / 10)) / 2 + fdf->xyadj[1];
	}
	return (xy);
}

void	clr_image(t_fdf *fdf, unsigned int color)
{
	char	*dst;
	int		x;

	x = 0;
	dst = fdf->img.addr;
	while (x < (fdf->wx) * (fdf->wy))
	{
		*(unsigned int *)dst = color;
		dst = dst + (fdf->img.bits_ppx / 8);
		x++;
	}
}

void	draw_text(t_fdf *fdf, int x, int y, char *text)
{
	mlx_string_put(fdf->vars.mlx, fdf->vars.win, x, y, 0x00000000, text);
	x += 2;
	y += 1;
	mlx_string_put(fdf->vars.mlx, fdf->vars.win, x, y, 0xFFFFFFFF, text);
}

void	draw_ui(t_fdf *fdf)
{
	int	i;

	i = 0;
	draw_text(fdf, 6, (i++) * 15 + 1, "ESC to quit");
	draw_text(fdf, 6, (i++) * 15 + 1, "Num +/- to scale height");
	draw_text(fdf, 6, (i++) * 15 + 1, "WASD to scroll");
	draw_text(fdf, 6, (i++) * 15 + 1,
		"Arrow keys & drag LMB to rotate and change plane");
	draw_text(fdf, 6, (i++) * 15 + 1, "ZX to zoom in/out");
	draw_text(fdf, 6, (i++) * 15 + 1, "QE to rotate");
	draw_text(fdf, 6, (i++) * 15 + 1, "C to change color mode");
	draw_text(fdf, 6, (i++) * 15 + 1, "P to change projection");
	draw_text(fdf, 6, (i++) * 15 + 1, "R to reset");
}
