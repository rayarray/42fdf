/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 10:43:50 by rleskine          #+#    #+#             */
/*   Updated: 2022/11/23 11:31:07 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static const char	*ft_pretrim(char const *s1, char const *set)
{
	const char	*setptr;

	setptr = set;
	while (*s1)
	{
		if (!*setptr)
			return (s1);
		else if (*s1 == *setptr)
		{
			setptr = set;
			s1++;
		}
		else
			setptr++;
	}
	return (s1);
}

static size_t	ft_suftrim(char const *s1, char const *set)
{
	const char	*setptr;
	size_t		size;

	size = 0;
	setptr = set;
	while (*s1)
	{
		size++;
		s1++;
	}
	s1--;
	while (size > 0)
	{
		if (!*setptr)
			return (size);
		else if (*s1 == *setptr)
		{
			setptr = set;
			s1--;
			size--;
		}
		else
			setptr++;
	}
	return (size);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	size;
	char	*trim;

	if (s1 == NULL || set == NULL)
		return (NULL);
	trim = (char *)ft_pretrim(s1, set);
	s1 = trim;
	size = ft_suftrim(s1, set);
	trim = (char *)malloc((size + 1) * sizeof(char));
	if (trim == NULL)
		return (NULL);
	set = trim;
	while (size)
	{
		*trim = *s1;
		trim++;
		s1++;
		size--;
	}
	*trim = 0;
	return ((char *)set);
}
