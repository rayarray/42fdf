/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 11:24:48 by rleskine          #+#    #+#             */
/*   Updated: 2022/11/23 11:53:54 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*haypos;
	char	*ndlpos;
	size_t	pos[2];

	if (haystack == NULL && len == 0)
		return (NULL);
	if (!*needle)
		return ((char *)haystack);
	pos[0] = 0;
	while (*haystack && pos[0] < len)
	{
		ndlpos = (char *)needle;
		haypos = (char *)haystack;
		pos[1] = ++pos[0];
		while (*haypos && *haypos == *ndlpos && (pos[1] - 1) < len)
		{
			haypos++;
			ndlpos++;
			pos[1]++;
			if (!*ndlpos)
				return ((char *)haystack);
		}
		haystack++;
	}
	return (NULL);
}
