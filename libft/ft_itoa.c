/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:17:42 by rleskine          #+#    #+#             */
/*   Updated: 2022/11/23 11:32:45 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	ft_intsize(size_t n)
{
	size_t	dec;

	dec = 1;
	while ((n / 10) > 0)
	{
		dec++;
		n = n / 10;
	}
	return (dec);
}

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

static size_t	ft_itoaabs(int n)
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

char	*ft_itoa(int n)
{
	size_t	num[2];
	char	*str[2];

	num[0] = ft_itoaabs(n);
	num[1] = ft_intsize(num[0]);
	if (n < 0)
		num[1]++;
	str[0] = (char *)malloc((num[1] + 1) * sizeof(char));
	if (str[0] == NULL)
		return (NULL);
	str[1] = str[0];
	if (n < 0)
	{
		*str[0] = '-';
		num[1]--;
		str[0]++;
	}
	while (num[1] > 0)
	{
		*str[0] = 48 + ft_firstnbr(num[0], num[1]);
		num[0] -= (ft_firstnbr(num[0], num[1]) * ft_powerten(--num[1]));
		str[0]++;
	}
	*str[0] = 0;
	return (str[1]);
}
