/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:10:40 by rleskine          #+#    #+#             */
/*   Updated: 2022/11/14 18:08:27 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*r1;
	unsigned char	*r2;
	size_t			pos;
	int				cmp;

	r1 = (unsigned char *)s1;
	r2 = (unsigned char *)s2;
	cmp = 0;
	pos = 0;
	while (pos < n)
	{
		cmp = cmp + (*r1 - *r2);
		pos++;
		if (cmp)
			return (cmp);
		r1++;
		r2++;
	}
	return (cmp);
}
