/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:03:40 by rleskine          #+#    #+#             */
/*   Updated: 2022/10/28 16:13:25 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_bzero(void *b, size_t len)
{
	size_t			pos;
	unsigned char	*s;

	s = (unsigned char *)b;
	pos = 0;
	while (pos < len)
	{
		*s = (unsigned char)0;
		s++;
		pos++;
	}
	return (b);
}
