/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:36:08 by rleskine          #+#    #+#             */
/*   Updated: 2023/04/26 11:50:50 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	get_index(char c, char *index)
{
	int	i;

	i = 0;
	while (index && index[i])
	{
		if (c == index[i])
			return (i);
		else
			i++;
	}
	return (-1);
}

int	check_tag(const char *format)
{
	const char	*pos;

	pos = format;
	if (*pos != 0 && get_index(*pos, "-0#+ ") > -1)
		while (*pos != 0 && get_index(*pos, "-0#+ ") > -1)
			pos++;
	if (*pos != 0 && *pos == '*')
		pos++;
	else
		while (*pos != 0 && *pos > 47 && *pos < 58)
			pos++;
	if (*pos != 0 && *pos == '.')
	{
		pos++;
		if (*pos != 0 && *pos == '*')
			pos++;
		else if (*pos != 0 && *pos > 47 && *pos < 58)
			while (pos != 0 && *pos > 47 && *pos < 58)
				pos++;
	}
	if (*pos != 0 && get_index(*pos, "cspdiuxX%") > -1)
		return ((int)(++pos - format));
	return (0);
}

int	calc_elemcount(const char *format)
{
	int	elemcount;
	int	elemsize;

	elemcount = 0;
	while (format && *format != 0)
	{
		elemcount++;
		if (*format == '%' && *(format + 1) != 0)
		{
			format++;
			elemsize = check_tag(format);
			if (elemsize < 1)
				return (-1);
			format = format + elemsize;
		}
		else
			while (*format != 0 && *format != '%')
				format++;
	}
	return (elemcount);
}

int	power(int base, int exp)
{
	int	result;

	if (exp == 0)
		return (1);
	result = base;
	while (exp-- > 1)
		result = result * base;
	return (result);
}

int	minmax(int n, ...)
{
	va_list	args;
	int		value;
	int		cmp;

	va_start(args, n);
	value = va_arg(args, int);
	if (n > 0)
		n--;
	else
		n++;
	while (n != 0)
	{
		cmp = va_arg(args, int);
		if (n < 0 && cmp < value)
			value = cmp;
		else if (n > 0 && cmp > value)
			value = cmp;
		if (n > 0)
			n--;
		else
			n++;
	}
	va_end(args);
	return (value);
}
