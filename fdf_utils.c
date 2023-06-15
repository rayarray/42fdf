/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:15:01 by rleskine          #+#    #+#             */
/*   Updated: 2023/05/22 15:53:48 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_init(t_fdf *fdf)
{
	fdf->wx = 1920;
	fdf->wy = 1080;
	fdf->vx = (fdf->wx * 10);
	fdf->vy = (fdf->wy * 10);
	fdf->zadj = 0;
	fdf->xyadj[0] = 0;
	fdf->xyadj[1] = 0;
	fdf->bgcolor = 0x000A2030;
	fdf->vars.mbutton = 0;
	fdf->rot2 = 45;
	fdf->pln = 45;
	fdf->clrmode = 0;
	fdf->refresh = 0;
	if (abs(fdf->map->max - fdf->map->min) >= 99)
		fdf->zscale = 25;
	else if (abs(fdf->map->max - fdf->map->min) >= 49)
		fdf->zscale = 50;
	else if (abs(fdf->map->max - fdf->map->min) >= 24)
		fdf->zscale = 75;
	else
		fdf->zscale = 90;
}

void	chk_rotate(t_fdf *fdf)
{
	if (fdf->rot2 >= 90)
	{
		fdf->rot2 -= 90;
		if (++(fdf->rot) > 3)
			fdf->rot = 0;
	}
	else if (fdf->rot2 <= -90)
	{
		fdf->rot2 += 90;
		if (--(fdf->rot) < 0)
			fdf->rot = 3;
	}
}

void	change_projection(t_fdf *fdf)
{
	fdf->pln = ((fdf->pln / 45) + 1) * 45;
	if (fdf->pln > 90)
		fdf->pln = 0;
}
