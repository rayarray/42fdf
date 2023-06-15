/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:19:01 by rleskine          #+#    #+#             */
/*   Updated: 2023/05/24 14:55:31 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	check_args(int ac, char **av)
{
	if (ac < 0)
	{
		perror("Error");
		return (0);
	}
	if (ac == 1)
		ft_printf("Please specify a map file to open\n");
	else if (ac > 2)
		ft_printf("Too many arguments\n");
	else if (ac == 2 && ft_strncmp(".fdf", av[1] + ft_strlen(av[1]) - 4, 4))
	{
		ft_printf("Warning! File name does not end in .fdf\n");
		return (1);
	}
	else
		return (1);
	return (0);
}

void	redraw_win(t_fdf *fdf)
{
	clr_image(fdf, fdf->bgcolor);
	draw_image(fdf, 0);
	mlx_put_image_to_window(fdf->vars.mlx, fdf->vars.win, fdf->img.img, 0, 0);
	draw_ui(fdf);
}

void	gfx_init(t_fdf *fdf)
{
	fdf->vars.mlx = mlx_init();
	fdf->vars.win = mlx_new_window(fdf->vars.mlx, fdf->wx, fdf->wy, "fdf");
	fdf->img.img = mlx_new_image(fdf->vars.mlx, fdf->wx, fdf->wy);
	fdf->img.addr = mlx_get_data_addr(fdf->img.img, &fdf->img.bits_ppx,
			&fdf->img.len, &fdf->img.endian);
	fdf->vars.img = &(fdf->img);
}

int	main(int ac, char **av)
{
	t_fdf		fdf;
	extern int	errno;

	if (check_args(ac, av) == 0)
		return (0);
	fdf.fd = open(av[1], O_RDWR);
	if (fdf.fd == -1 && errno == EISDIR)
		return (check_args(-1, NULL));
	else
		fdf.fd = open(av[1], O_RDONLY);
	if (fdf.fd == -1)
		return (check_args(-1, NULL));
	fdf.map = readmap(fdf.fd);
	if (close(fdf.fd))
		return (check_args(-1, NULL));
	fdf_init(&fdf);
	fdf.rot = 0;
	gfx_init(&fdf);
	redraw_win(&fdf);
	mlx_key_hook(fdf.vars.win, key_hook, &fdf);
	mlx_hook(fdf.vars.win, 17, 0, winexpose_hook, &fdf);
	mlx_hook(fdf.vars.win, 4, 0, mousebutton_hook, &fdf);
	mlx_hook(fdf.vars.win, 5, 0, mousebutton_hook, &fdf);
	mlx_hook(fdf.vars.win, 6, 0, mousemove_hook, &fdf);
	mlx_loop(fdf.vars.mlx);
}
