/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:22:46 by rleskine          #+#    #+#             */
/*   Updated: 2022/10/31 14:57:48 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	pos;
	int		cmp;

	cmp = 0;
	pos = 0;
	while (pos < n && (*s1 || *s2))
	{
		cmp = cmp + ((unsigned char)*s1 - (unsigned char)*s2);
		pos++;
		if (cmp)
			return (cmp);
		if (*s1)
			s1++;
		if (*s2)
			s2++;
	}
	return (cmp);
}
