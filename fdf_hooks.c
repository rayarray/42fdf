/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:15:21 by rleskine          #+#    #+#             */
/*   Updated: 2023/05/24 13:34:03 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	mousemove_hook(int x, int y, t_fdf *fdf)
{
	if (fdf->vars.mbutton == 1 && (1 || x))
	{
		if (x - fdf->vars.mx >= 360)
		{
			fdf->rot += 1;
			if (fdf->rot > 3)
				fdf->rot -= 4;
			fdf->vars.mx += 360;
		}
		else if (x - fdf->vars.mx <= -360)
		{
			fdf->rot -= 1;
			if (fdf->rot < 0)
				fdf->rot += 4;
			fdf->vars.mx -= 360;
		}
		fdf->rot2 = (x - fdf->vars.mx) / 4;
		fdf->pln = (y - fdf->vars.my) / 4;
		redraw_win(fdf);
	}
	return (0);
}

int	mousebutton_hook(int button, int x, int y, t_fdf *fdf)
{
	if (fdf->vars.mbutton == button && (1 || x))
		fdf->vars.mbutton = 0;
	else
		fdf->vars.mbutton = button;
	if (button == 1)
	{
		fdf->vars.mx = x - (fdf->rot2 * 4);
		fdf->vars.my = y - (fdf->pln * 4);
	}
	return (0);
}

int	key_hook(int keycode, t_fdf *fdf)
{
	if (keycode == 19 && ++(fdf->refresh) && ++(fdf->rot) == 4)
		fdf->rot = 0;
	else if (keycode == 18 && ++(fdf->refresh) && --(fdf->rot) == -1)
		fdf->rot = 3;
	else if (keycode == 69 && ++(fdf->refresh))
		fdf->zadj += 5;
	else if (keycode == 78 && ++(fdf->refresh))
		fdf->zadj -= 5;
	else if (keycode == 6 && ++(fdf->refresh))
	{
		fdf->vx = (fdf->vx * 11) / 10;
		fdf->vy = (fdf->vy * 11) / 10;
	}
	else if (keycode == 7 && ++(fdf->refresh))
	{
		fdf->vx = (fdf->vx * 9) / 10;
		fdf->vy = (fdf->vy * 9) / 10;
	}
	else if (keycode == 13 && ++(fdf->refresh))
		fdf->xyadj[1] += 50;
	else if (keycode == 1 && ++(fdf->refresh))
		fdf->xyadj[1] -= 50;
	else if (keycode == 0 && ++(fdf->refresh))
		fdf->xyadj[0] += 50;
	return (key_hook2(keycode, fdf));
}

int	key_hook2(int keycode, t_fdf *fdf)
{
	if (keycode == 2 && ++(fdf->refresh))
		fdf->xyadj[0] -= 50;
	else if (keycode == 123 && ++(fdf->refresh))
		fdf->rot2 -= 5;
	else if (keycode == 124 && ++(fdf->refresh))
		fdf->rot2 += 5;
	else if (keycode == 126 && ++(fdf->refresh))
		fdf->pln -= 5;
	else if (keycode == 125 && ++(fdf->refresh))
		fdf->pln += 5;
	else if (keycode == 8 && ++(fdf->refresh) && ++(fdf->clrmode) == 4)
		fdf->clrmode = 0;
	else if (keycode == 15)
		fdf_init(fdf);
	else if (keycode == 35 && ++(fdf->refresh))
		change_projection(fdf);
	else if (keycode == 53)
	{
		mlx_destroy_window(fdf->vars.mlx, fdf->vars.win);
		exit (0);
	}
	if (fdf->refresh > 0 || keycode == 15)
		redraw_win(fdf);
	return (0);
}

int	winexpose_hook(t_fdf *fdf)
{
	key_hook(53, fdf);
	return (0);
}
