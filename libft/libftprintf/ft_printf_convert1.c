/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_convert1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 09:53:30 by rleskine          #+#    #+#             */
/*   Updated: 2023/04/26 11:51:48 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	cnv_s(va_list args, t_flags *f, int i, int spec)
{
	char	*arg;

	arg = va_arg(args, char *);
	if (arg == NULL && --(f->size))
		arg = ft_strdup("(null)");
	s_helper(f, (int)ft_strlen(arg), arg);
	if (f->tmp == NULL)
		return ;
	while (f->leftpad == 1 && f->i < f->precision && *(arg + f->i))
	{
		*(f->tmp + f->i) = *(arg + f->i);
		(f->i)++;
	}
	spec = f->i + f->precision;
	while (f->leftpad != 1 && f->i < spec && *(arg + i))
	{
		*(f->tmp + f->i) = *(arg + i++);
		(f->i)++;
	}
	if (f->size == -1)
		free(arg);
}

void	cnv_c(va_list args, t_flags *flags, int i, int spec)
{
	char	c;

	if (spec == 1)
		c = '%';
	else
		c = (char)va_arg(args, int);
	if (flags->width < 1)
		flags->width = 1;
	if (c == 0)
	{
		flags->tmp = alloc_elem(flags->width, 1, 1, 128);
		if (flags->leftpad == 1)
			*(flags->tmp + 6) = '0';
		else
			*(flags->tmp + flags->width + 5) = '0';
		return ;
	}
	else
		flags->tmp = alloc_elem(flags->width, 0, -1, 128);
	if (flags->tmp == NULL)
		return ;
	if (flags->leftpad == 1 && ++i)
		*flags->tmp = c;
	if (flags->leftpad != 1)
		*(flags->tmp + flags->width - 1) = c;
}

void	cnv_d(va_list args, t_flags *f, int i, int spec)
{
	spec = (int)va_arg(args, int);
	if (f->width == 0 && f->precision == 0 && spec == 0)
		f->tmp = ft_strdup(")nULl(");
	if (f->width == 0 && f->precision == 0 && spec == 0)
		return ;
	if (f->leftpad == 2 && f->precision <= f->width && spec < 0)
		i = 1;
	if (f->leftpad == 2 && f->precision == -1)
		f->precision = f->width - i;
	getsize(f, &spec, 1, 10);
	f->width = minmax(3, f->width, f->precision, f->size);
	i = getsize(f, &spec, 1, 10);
	f->tmp = alloc_elem(f->width, 0, -1, 0);
	if (f->tmp == NULL)
		return ;
	if (f->leftpad == 2 && f->size < f->width && spec != 0)
		i = f->width - f->size;
	if (spec < 0)
		formatnbr(f->tmp + i, "-", f->precision, spec);
	else if (f->pre == 1)
		formatnbr(f->tmp + i, "+", f->precision, spec);
	else if (f->pre == 2)
		formatnbr(f->tmp + i, " ", f->precision, spec);
	else
		formatnbr(f->tmp + i, NULL, f->precision, spec);
}

void	cnv_x(va_list args, t_flags *flags, int i, int spec)
{
	unsigned long int	arg;

	if (spec == 2)
		p_helper(args, flags, &arg);
	else
		arg = va_arg(args, unsigned int);
	if (arg == 0 && flags->width < 1)
		flags->zero = 1;
	if (spec != 2 && arg == 0 && flags->pre == 3)
		flags->pre = 0;
	if (flags->leftpad == 2 && flags->precision == -1)
		flags->precision = flags->width;
	getsize(flags, NULL, arg, 16);
	flags->width = minmax(3, flags->width, flags->precision, flags->size);
	i = getsize(flags, NULL, arg, 16);
	flags->tmp = alloc_elem(flags->width, flags->zero, flags->precision, 0);
	if (flags->tmp == NULL || (flags->width == 6 && flags->precision == 0))
		return ;
	if (flags->pre == 3 && spec == 2)
		formatunbr(flags->tmp + i, "0x", flags->precision, arg);
	else if (flags->pre == 3)
		formatunbr(flags->tmp + i, "h0x", flags->precision, arg);
	else if ((flags->precision > 0 || arg != 0))
		formatunbr(flags->tmp + i, "h", flags->precision, arg);
}

void	cnv_u(va_list args, t_flags *f, int i, int spec)
{
	unsigned int	arg;

	arg = (unsigned int)va_arg(args, void *);
	if (f->width == 0 && f->precision == 0 && arg == 0)
		f->tmp = ft_strdup(")nULl(");
	if (f->width == 0 && f->precision == 0 && arg == 0)
		return ;
	if (f->leftpad == 2 && f->precision == -1 && ++spec)
		f->precision = f->width;
	getsize(f, NULL, arg, 10);
	f->width = minmax(3, f->width, f->precision, f->size);
	i = getsize(f, NULL, arg, 10);
	f->tmp = alloc_elem(f->width, 0, -1, 0);
	if (f->tmp == NULL)
		return ;
	if (f->leftpad == 2 && f->size < f->width && arg != 0)
		i = f->width - f->size;
	if (f->pre == 1)
		formatunbr(f->tmp + i, "d+", f->precision, arg);
	else if (f->pre == 2)
		formatunbr(f->tmp + i, "d ", f->precision, arg);
	else
		formatunbr(f->tmp + i, "d", f->precision, arg);
}
