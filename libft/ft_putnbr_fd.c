/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:37:00 by rleskine          #+#    #+#             */
/*   Updated: 2022/11/14 17:24:01 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static size_t	ft_firstnbr(size_t n, size_t dec)
{
	while (dec > 1)
	{
		n = n / 10;
		dec--;
	}
	return (n);
}

static size_t	ft_powerten(size_t n)
{
	size_t	res;

	res = 1;
	while (n > 0)
	{
		res = res * 10;
		n--;
	}
	return (res);
}

static size_t	ft_abs(int n)
{
	size_t	abs;

	if (n == -2147483648)
		abs = 2147483648;
	else if (n < 0)
		abs = (size_t) - n;
	else
		abs = (size_t)n;
	return (abs);
}

void	ft_putnbr_fd(int n, int fd)
{
	size_t	num[2];
	char	c;

	c = '-';
	num[1] = 1;
	num[0] = ft_abs(n);
	while (num[0] > 9)
	{
		num[0] = num[0] / 10;
		num[1]++;
	}
	num[0] = ft_abs(n);
	if (n < 0)
		write(fd, &c, 1);
	while (num[1] > 0)
	{
		c = 48 + ft_firstnbr(num[0], num[1]);
		write(fd, &c, 1);
		num[0] -= ft_firstnbr(num[0], num[1]) * ft_powerten(num[1] - 1);
		num[1]--;
	}
}
