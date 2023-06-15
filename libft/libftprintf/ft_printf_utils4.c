/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:28:58 by rleskine          #+#    #+#             */
/*   Updated: 2023/02/24 19:44:27 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	s_helper(t_flags *flags, int len, char *arg)
{
	arg += 0;
	if (len < flags->precision || flags->precision == -1)
		flags->width = minmax(2, flags->width, len);
	else
		flags->width = minmax(2, flags->width, flags->precision);
	if (flags->precision != -1)
		flags->width = \
			minmax(2, flags->width, minmax(-2, flags->precision, len));
	else
		flags->precision = len;
	flags->tmp = alloc_elem(flags->width, 0, -5, 0);
	if (flags->leftpad != 1 && flags->precision != -1)
	{
		if (len < flags->precision)
			flags->i = flags->width - len;
		else
			flags->i = flags->width - flags->precision;
	}
	else if (flags->leftpad != 1 && flags->precision == -1)
		flags->i = flags->width - len;
	return (flags->i);
}

void	p_helper(va_list args, t_flags *flags, unsigned long int *arg)
{
	flags->pre = 3;
	*arg = (unsigned long int)va_arg(args, void *);
	if (*arg == 0)
		flags->precision = minmax(-2, minmax(2, flags->precision, 1));
	else
		flags->precision = \
			minmax(-2, minmax(2, flags->precision, 9), \
				getdigits(*arg, NULL, 16));
}
