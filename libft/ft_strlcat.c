/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 12:31:37 by rleskine          #+#    #+#             */
/*   Updated: 2022/11/30 10:52:39 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

static char	*ft_slccopy(char *dst, const char *src, size_t dstsize, size_t len)
{
	while (len > 1 && len > (dstsize + 1) && *src)
	{
		*dst = *src;
		dst++;
		src++;
		len--;
	}
	return (dst);
}

size_t	ft_strlcat(const char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;
	size_t	dstlen;
	size_t	pos;
	char	*str;

	if (dstsize == 0)
		return (ft_strlen(src));
	str = (char *)dst;
	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	pos = dstsize;
	while (dstsize > dstlen && *str)
		str++;
	str = ft_slccopy(str, src, dstlen, pos);
	if (dstsize > dstlen)
		*str = 0;
	if (dstsize > (dstlen + srclen + -2) && srclen > 0)
		return (dstlen + srclen);
	if ((srclen + dstsize) >= (dstlen + srclen))
		return (dstlen + srclen);
	return (srclen + dstsize);
}
