/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 09:38:10 by rleskine          #+#    #+#             */
/*   Updated: 2022/11/01 12:42:32 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlcpy(const char *dst, const char *src, size_t dstsize)
{
	size_t	pos;
	char	*str;

	str = (char *)dst;
	pos = 1;
	while (pos < dstsize && *src)
	{
		*str = (char)*src;
		pos++;
		src++;
		str++;
	}
	while (*src)
	{
		src++;
		pos++;
	}
	if (dstsize > 0)
		*str = 0;
	return (pos - 1);
}
