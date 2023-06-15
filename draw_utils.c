/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:07:51 by rleskine          #+#    #+#             */
/*   Updated: 2023/05/22 14:19:49 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	chk_visible2(t_fdf *fdf, int xy[4], t_rgbline *ln)
{
	while (1)
	{
		if (xy[0] > -1 && xy[0] < fdf->wx && xy[1] > -1 && xy[1] < fdf->wy)
			return (1);
		if (xy[0] == xy[2] && xy[1] == xy[3])
			break ;
		ln->err2 = 2 * ln->err;
		if (ln->err2 > -ln->dy)
		{
			ln->err -= ln->dy;
			xy[0] += ln->sx;
		}
		if (ln->err2 < ln->dx)
		{
			ln->err += ln->dx;
			xy[1] += ln->sy;
		}
	}
	return (0);
}

int	chk_visible(t_fdf *fdf, int xy[4])
{
	t_rgbline	ln;

	ln.dx = abs(xy[2] - xy[0]);
	ln.dy = abs(xy[3] - xy[1]);
	if (xy[0] < xy[2])
		ln.sx = 1;
	else
		ln.sx = -1;
	if (xy[1] < xy[3])
		ln.sy = 1;
	else
		ln.sy = -1;
	ln.err = ln.dx - ln.dy;
	return (chk_visible2(fdf, xy, &ln));
}

void	grad_line2(t_rgbline *ln, t_fdf *fdf)
{
	ln->pos = 0;
	ln->err = ln->dx - ln->dy;
	while (ln->x1 != ln->x2 || ln->y1 != ln->y2)
	{
		ln->rgb2 = ln->rgb;
		ln->rgb2 += ((ln->rd * ((++(ln->pos) * 10) / ln->len)) / 10) << 16;
		ln->rgb2 += ((ln->gd * ((ln->pos * 10) / ln->len)) / 10) << 8;
		ln->rgb2 += ((ln->bd * ((ln->pos * 10) / ln->len)) / 10);
		put_pixel(fdf, ln->x1, ln->y1, ln->rgb2);
		ln->err2 = 2 * ln->err;
		if (ln->err2 > -ln->dy)
		{
			ln->err -= ln->dy;
			ln->x1 += ln->sx;
		}
		if (ln->err2 < ln->dx)
		{
			ln->err += ln->dx;
			ln->y1 += ln->sy;
		}
	}
	put_pixel(fdf, ln->x2, ln->y2, ln->rgb + ln->rd + ln->gd + ln->bd);
}

void	grad_line(int xy[4], int argb, int argb2, t_fdf *fdf)
{
	t_rgbline	*ln;

	ln = &fdf->ln;
	if ((xy[0] < 0 && xy[2] < 0) || (xy[0] > fdf->wx && xy[2] > fdf->wx))
		return ;
	ln->x1 = xy[0];
	ln->x2 = xy[2];
	ln->y1 = xy[1];
	ln->y2 = xy[3];
	ln->rgb = argb;
	ln->rd = ((argb2 & 0xFF0000) - (argb & 0xFF0000)) >> 16;
	ln->gd = (argb2 >> 8 & 0xFF) - (argb >> 8 & 0xFF);
	ln->bd = (argb2 & 0xFF) - (argb & 0xFF);
	ln->len = minmax(2, abs(xy[0] - xy[2]), abs(xy[1] - xy[3]));
	ln->dx = abs(ln->x2 - ln->x1);
	ln->dy = abs(ln->y2 - ln->y1);
	if (ln->x1 < ln->x2)
		ln->sx = 1;
	else
		ln->sx = -1;
	if (ln->y1 < ln->y2)
		ln->sy = 1;
	else
		ln->sy = -1;
	grad_line2(ln, fdf);
}
