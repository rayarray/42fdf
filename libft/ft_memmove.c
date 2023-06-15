/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:50:44 by rleskine          #+#    #+#             */
/*   Updated: 2022/11/14 18:24:21 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *dst, void *src, size_t n)
{
	size_t	pos;

	pos = 0;
	if (src < dst)
	{
		while (n > 0)
		{
			*(unsigned char *)(dst + n - 1) = *(unsigned char *)(src + n - 1);
			n--;
		}
	}
	else if (src > dst)
	{
		while (pos < n)
		{
			*(unsigned char *)(dst + pos) = \
				*(unsigned char *)(src + pos);
			pos++;
		}
	}
	return (dst);
}
