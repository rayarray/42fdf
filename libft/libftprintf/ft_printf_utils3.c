/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:28:58 by rleskine          #+#    #+#             */
/*   Updated: 2023/02/24 19:36:14 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	getsize(t_flags *f, int *arg, unsigned long int uarg, int base)
{
	if (f->width == 0 && f->precision == 0 && ((arg && arg == 0) || uarg == 0))
	{
		f->width = 6;
		return (0);
	}
	if (arg == NULL)
		f->size = getdigits(uarg, NULL, base);
	else
		f->size = getdigits(0, arg, base);
	if (f->precision == -1 || (f->precision < f->size && \
		f->precision != 0 && ((arg && *arg) || uarg != 0)))
		f->precision = f->size;
	if (f->precision > f->size)
		f->size = f->precision;
	if (arg != NULL && (*arg < 0 || f->pre == 1 || f->pre == 2))
		f->size++;
	else if (arg == NULL && f->pre == 3)
		f->size += 2;
	if (f->leftpad == 2 && f->width > f->size)
		return (f->width - f->size);
	else if (f->leftpad == 1 || f->leftpad == 2)
		return (0);
	else
		return (minmax(2, f->width - f->size, 0));
}

void	signcopy(char *s, int nbr, int size, int base)
{
	char	c;

	while (size)
	{
		if (nbr % base < 0)
			c = 48 - (nbr % base);
		else
			c = 48 + (nbr % base);
		if (c > 57)
			c += 39;
		nbr = nbr / base;
		*(s + --size) = c;
	}
}

void	unsigncopy(char *s, unsigned long int nbr, int size, int base)
{
	char	c;

	while (size)
	{
		c = 48 + (nbr % base);
		if (c > 57)
			c += 39;
		nbr = nbr / base;
		*(s + --size) = c;
	}
}

void	formatnbr(char *s, char *sign, int zeroes, int nbr)
{
	int	base;

	if (zeroes < 1 && nbr == 0)
		return ;
	base = 10;
	if (sign && *sign == 'z' && sign++ && nbr < 0)
		zeroes--;
	if (sign && *sign == 'h' && sign++)
		base = 16;
	while (sign && *sign)
	{
		*s = *sign;
		s++;
		if (*sign == '-' && nbr > -1)
			s--;
		sign++;
	}
	zeroes -= getdigits(0, &nbr, base);
	while (zeroes > 0)
	{
		*s = '0';
		zeroes--;
		s++;
	}
	signcopy(s, nbr, getdigits(0, &nbr, base), base);
}

void	formatunbr(char *s, char *sign, int zeroes, unsigned long int nbr)
{
	int	base;

	if (zeroes < 1 && nbr == 0 && sign && (*sign == 'd' || *sign == 'h'))
		return ;
	base = 16;
	if (sign && *sign == 'd' && sign++)
		base = 10;
	else if (sign && *sign == 'h')
		sign++;
	while (sign && *sign)
	{
		*s = *sign;
		s++;
		sign++;
	}
	zeroes -= getdigits(nbr, NULL, base);
	while (zeroes > 0)
	{
		*s = '0';
		zeroes--;
		s++;
	}
	unsigncopy(s, nbr, getdigits(nbr, NULL, base), base);
}
