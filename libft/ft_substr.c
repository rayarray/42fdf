/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:04:13 by rleskine          #+#    #+#             */
/*   Updated: 2022/11/29 11:06:42 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	char	*sub;

	if (s == NULL)
		return (NULL);
	while (*s && start && s++)
		start--;
	if (!*s && start > 0)
		start = 0;
	str = (char *)s;
	while (*str && len > start && str++)
		start++;
	sub = (char *)malloc((start + 1) * sizeof(char));
	if (sub == NULL)
		return (NULL);
	str = sub;
	while (start && *s)
	{
		*sub = *s;
		sub++;
		s++;
		start--;
	}
	*sub = 0;
	return (str);
}
