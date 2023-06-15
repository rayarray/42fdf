/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 12:42:38 by rleskine          #+#    #+#             */
/*   Updated: 2023/05/22 15:51:49 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <mlx.h>
# include "libft/libft.h"

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_ppx;
	int		len;
	int		endian;
}	t_data;

typedef struct s_vars {
	void	*mlx;
	void	*win;
	t_data	*img;
	t_data	*img2;
	int		mbutton;
	int		mx;
	int		my;
}	t_vars;

typedef struct s_map
{
	int				**z;
	int				**rgb;
	int				col;
	int				row;
	int				pos;
	int				min;
	int				max;
	int				fd;
}	t_map;

typedef struct s_rgbline {
	int				x1;
	int				x2;
	int				y1;
	int				y2;
	int				dx;
	int				dy;
	int				sx;
	int				sy;
	unsigned int	rgb;
	unsigned int	rgb2;
	int				rd;
	int				gd;
	int				bd;
	int				pos;
	int				len;
	int				err;
	int				err2;
}	t_rgbline;

typedef struct s_fdf {
	t_vars			vars;
	t_data			img;
	t_data			img2;
	t_map			*map;
	t_rgbline		ln;
	int				*cache;
	int				refresh;
	int				wx;
	int				wy;
	int				vx;
	int				vy;
	unsigned int	bgcolor;
	int				ratio;
	double			xlen;
	double			ylen;
	int				zoom;
	int				x0;
	int				y0;
	int				xyadj[2];
	int				zscale;
	int				zadj;
	int				rot;
	int				rot2;
	double			rrad;
	int				pln;
	double			prad;
	int				clrmode;
	int				fd;
	double			rx;
	double			ry;
	int				vrow[2];
}	t_fdf;

// Map reading functions

int				get_rowsize(char *line, int x);
char			*parse_value(char *line, int *val, int *rgb);
int				hex_atoi(char *line, int nbr);
void			update_minmax(t_map *map, int value);
t_map			*readmap(int fd);

// Drawing functions

void			draw_image(t_fdf *fdf, int i);
int				getxy(t_fdf *fdf, int rot, int xy[2], int val);
void			rot_xy(t_fdf *fdf, int x, int y);
unsigned int	get_color(t_fdf *fdf, int x, int y);
int				chk_vposs(t_fdf *fdf, double wxy[4]);
double			get_wxy(t_fdf *fdf, int x, int y, int dim);
void			clr_image(t_fdf *fdf, unsigned int color);
int				get_pxinline(int xy[4]);
int				chk_visible(t_fdf *fdf, int xy[4]);
void			put_pixel(t_fdf *fdf, int x, int y, unsigned int color);
void			my_mlx_pixel_put(t_fdf *fdf, int x, int y, int color);
void			norm_line(int xy[4], int argb, t_fdf *fdf);
void			grad_line(int xy[4], int argb, int argb2, t_fdf *fdf);
int				get_zscale(t_fdf *fdf, int rot, int min_z);
void			draw_box(t_fdf *fdf, int xy[4], int color);
void			draw_ui(t_fdf *fdf);

// Keyboard & mouse hooks

int				mousemove_hook(int x, int y, t_fdf *fdf);
int				mousebutton_hook(int button, int x, int y, t_fdf *fdf);
int				key_hook(int keycode, t_fdf *fdf);
int				key_hook2(int keycode, t_fdf *fdf);
int				winexpose_hook(t_fdf *fdf);

// Other helper functions

void			free_fdf(t_fdf *fdf);
void			redraw_win(t_fdf *fdf);
void			fdf_init(t_fdf *fdf);
void			rotate_xy(t_fdf *fdf, int xy[3], int x, int y);
void			change_projection(t_fdf *fdf);

#endif /* FDF_H */