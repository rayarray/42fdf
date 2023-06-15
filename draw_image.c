/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:30:42 by rleskine          #+#    #+#             */
/*   Updated: 2023/05/24 13:35:15 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	getxy(t_fdf *fdf, int rot, int xy[2], int val)
{
	if ((val == 2 && (rot == 0 || rot == 2))
		|| (val == 3 && (rot == 1 || rot == 3)))
		return (fdf->map->col);
	else if (val == 2 || val == 3)
		return (fdf->map->row);
	if (val == 0 && rot == 0)
		return (fdf->map->z[xy[1]][xy[0]]);
	if (val == 0 && rot == 1)
		return (fdf->map->z[fdf->map->row - xy[0] - 1][xy[1]]);
	if (val == 0 && rot == 2)
		return (fdf->map->z[fdf->map->row - xy[1] - 1]
			[fdf->map->col - xy[0] - 1]);
	if (val == 0 && rot == 3)
		return (fdf->map->z[xy[0]][fdf->map->col - xy[1] - 1]);
	if (val == 1 && rot == 0)
		return (fdf->map->rgb[xy[1]][xy[0]]);
	if (val == 1 && rot == 1)
		return (fdf->map->rgb[fdf->map->row - xy[0] - 1][xy[1]]);
	if (val == 1 && rot == 2)
		return (fdf->map->rgb[fdf->map->row - xy[1] - 1]
			[fdf->map->col - xy[0] - 1]);
	if (val == 1 && rot == 3)
		return (fdf->map->rgb[xy[0]][fdf->map->col - xy[1] - 1]);
	return (-1);
}

void	get_visible2(t_fdf *fdf, double wxy[4], int x, int y)
{
	while (y > fdf->vrow[0])
	{
		rot_xy(fdf, 0, y);
		wxy[0] = get_wxy(fdf, 0, y, 0);
		wxy[1] = get_wxy(fdf, 0, y, 1);
		rot_xy(fdf, x, y);
		wxy[2] = get_wxy(fdf, x, y, 0);
		wxy[3] = get_wxy(fdf, x, y, 1);
		if (chk_vposs(fdf, wxy) && chk_visible(fdf,
				(int [4]){wxy[0], wxy[1], wxy[2], wxy[3]}))
			break ;
		y--;
	}
	fdf->vrow[1] = y + 1;
}

void	get_visible(t_fdf *fdf, double wxy[4], int x, int y)
{
	while (y < getxy(fdf, fdf->rot, NULL, 3))
	{
		rot_xy(fdf, 0, y);
		wxy[0] = get_wxy(fdf, 0, y, 0);
		wxy[1] = get_wxy(fdf, 0, y, 1);
		rot_xy(fdf, x, y);
		wxy[2] = get_wxy(fdf, x, y, 0);
		wxy[3] = get_wxy(fdf, x, y, 1);
		if (chk_vposs(fdf, wxy) && chk_visible(fdf,
				(int [4]){wxy[0], wxy[1], wxy[2], wxy[3]}))
			break ;
		y++;
	}
	fdf->vrow[0] = minmax(2, 0, y - 1);
	y = getxy(fdf, fdf->rot, NULL, 3) - 1;
	get_visible2(fdf, wxy, x, y);
}

void	draw_fdf2(t_fdf *fdf, double wxy[3], int xy[2], int draw)
{
	while (xy[0] < getxy(fdf, fdf->rot, NULL, 2))
	{
		wxy[0] = get_wxy(fdf, xy[0], xy[1], 0);
		wxy[1] = get_wxy(fdf, xy[0], xy[1], 1);
		wxy[1] -= cos(fdf->prad) * getxy(fdf, fdf->rot, xy, 0)
			* (fdf->zscale + fdf->zadj) / 10;
		wxy[2] = get_color(fdf, xy[0], xy[1]);
		if (draw && xy[1] > 0)
			grad_line((int [4]){*(fdf->cache + (xy[0] * 2)),
				*(fdf->cache + (xy[0] * 2) + 1), wxy[0], wxy[1]},
				get_color(fdf, xy[0], xy[1] - 1), wxy[2], fdf);
		if (draw && xy[0] > 0)
			grad_line((int [4]){wxy[0], wxy[1], *(fdf->cache + (xy[0] * 2) - 2),
				*(fdf->cache + (xy[0] * 2) - 1)}, wxy[2],
				get_color(fdf, xy[0] - 1, xy[1]), fdf);
		*(fdf->cache + (xy[0] * 2)) = wxy[0];
		*(fdf->cache + (xy[0] * 2) + 1) = wxy[1];
		xy[0]++;
	}
}

void	draw_image(t_fdf *fdf, int i)
{
	t_map	*map;
	int		*colrow;

	map = fdf->map;
	if (map->col == 0 || map->row == 0)
		return ;
	fdf->rrad = fdf->rot2 * M_PI / 180;
	fdf->prad = fdf->pln * M_PI / 180;
	if (fdf->rot == 0 || fdf->rot == 2)
		colrow = (int [2]){map->col, map->row};
	else
		colrow = (int [2]){map->row, map->col};
	fdf->cache = (int *)malloc(sizeof(int) * colrow[0] * 2);
	if (fdf->cache == NULL)
		return ;
	fdf->xlen = fdf->vx / (map->col + map->row - 2);
	fdf->ylen = fdf->xlen;
	fdf->x0 = (fdf->vx - ((colrow[0] - 1) * fdf->xlen)) / 20;
	fdf->y0 = (fdf->vy - ((colrow[1] - 1) * fdf->ylen)) / 20;
	get_visible(fdf, (double [4]){0, 0, 0, 0}, colrow[0] - 1, 0);
	draw_fdf2(fdf, (double [3]){0, 0, 0}, (int [2]){0, (fdf->vrow[0])++}, 0);
	while (i < fdf->vrow[1])
		draw_fdf2(fdf, (double [3]){0, 0, 0}, (int [2]){0, i++}, 1);
	free(fdf->cache);
}
