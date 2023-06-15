/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:35:39 by rleskine          #+#    #+#             */
/*   Updated: 2022/11/29 10:27:34 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	ft_splitn(char const *s, char c)
{
	size_t	nbr;

	nbr = 0;
	if (s == NULL)
		return (0);
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s && *s != c)
			nbr++;
		while (*s && *s != c)
			s++;
	}
	return (nbr);
}

static size_t	ft_splits(char const *s, char c)
{
	size_t	nbr;

	nbr = 0;
	while (*s && *s != c)
	{
		s++;
		nbr++;
	}
	return (nbr);
}

static int	ft_splitcpy(char const *src, char *dst, char c)
{
	while (*src && *src != c)
	{
		*dst = *src;
		dst++;
		src++;
	}
	*dst = 0;
	return (1);
}

static int	ft_splitfree(char **s)
{
	char	**tmp;

	tmp = s;
	while (*s != NULL)
	{
		free (*s);
		s++;
	}
	free (tmp);
	return (1);
}

char	**ft_split(char const *s, char c)
{
	size_t	pos;
	char	**split;
	char	**ret;

	pos = ft_splitn(s, c);
	split = (char **)malloc((pos + 1) * sizeof(char *));
	if (split == NULL || s == NULL)
		return (NULL);
	ret = split;
	while (pos-- > 0)
	{
		while (*s == c)
			s++;
		*split = (char *)malloc((ft_splits(s, c) + 1) * sizeof(char));
		if (*split == NULL && ft_splitfree(ret))
			return (NULL);
		if (ft_splitcpy(s, *split, c) == 1 && split++)
			while (*s && *s != c)
				s++;
	}
	*split = NULL;
	return (ret);
}
