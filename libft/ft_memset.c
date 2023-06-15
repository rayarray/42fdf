/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:56:41 by rleskine          #+#    #+#             */
/*   Updated: 2022/11/14 17:30:14 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			pos;
	unsigned char	*s;

	s = (unsigned char *)b;
	pos = 0;
	while (pos < len)
	{
		*s = c;
		s++;
		pos++;
	}
	return (b);
}
