/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:58:24 by rleskine          #+#    #+#             */
/*   Updated: 2022/11/14 18:54:00 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*r;

	r = (unsigned char *)s;
	while (n > 0)
	{
		if (*r == (unsigned char)c)
			return ((char *)r);
		r++;
		n--;
	}
	return ((char *)0);
}
