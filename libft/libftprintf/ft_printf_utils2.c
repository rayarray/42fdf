/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:28:58 by rleskine          #+#    #+#             */
/*   Updated: 2023/04/26 11:51:23 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*alloc_elem(int size, int zero, int nullcase, int i)
{
	char	*str;

	str = NULL;
	if (nullcase == 1 && i == 128)
		size += 6;
	if (size < 1)
	{
		size = 6;
		nullcase = 1;
		zero = 1;
	}
	i = size;
	if (size > 0)
	{
		str = (char *)malloc(sizeof(char) * (size + 1));
		if (str == NULL)
			return (NULL);
		*(str + size) = 0;
		while (size > 0)
			*(str + size-- - 1) = ' ';
	}
	if (i > 5 && zero == 1 && (nullcase == 1 || nullcase == 0))
		ft_memcpy(str, ")nULl(", 6);
	return (str);
}

void	cnv_case(char *s, int lcase)
{
	if (lcase == 1)
		lcase = -32;
	else
		lcase = 32;
	while (s && *s)
	{
		if (lcase == -32 && *s > 96 && *s < 123)
			*s = *s + lcase;
		else if (lcase == 32 & *s > 64 && *s < 91)
			*s = *s + lcase;
		s++;
	}
}

t_flags	*init_flags(const char *format, t_flags *flags)
{
	if (flags == NULL)
	{
		flags = (t_flags *)malloc(sizeof(t_flags));
		if (flags == NULL)
			return (flags);
		flags->size = calc_elemcount(format);
	}
	else
		flags->size = 0;
	flags->leftpad = 0;
	flags->width = 0;
	flags->precision = -1;
	flags->pre = 0;
	flags->i = 0;
	flags->zero = 0;
	flags->tmp = NULL;
	return (flags);
}

int	getdigits(unsigned long int nbr, int *nbrptr, int base)
{
	int	digits;

	if (nbrptr != NULL)
	{
		if (*nbrptr < 0)
			nbr = 0 - (unsigned long int)*nbrptr;
		else
			nbr = *nbrptr;
	}
	digits = 0;
	if (nbr == 0)
		return (1);
	while (nbr != 0 && ++digits)
		nbr = nbr / base;
	return (digits);
}

int	getnumsize(const char *format)
{
	int	size;

	size = 0;
	while (*format == 48)
		format++;
	while (*format > 47 && *format < 58)
	{
		format++;
		size++;
	}
	return (size);
}
