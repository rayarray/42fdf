/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 11:04:30 by rleskine          #+#    #+#             */
/*   Updated: 2022/10/28 16:15:51 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char	*r;

	r = 0;
	if (!*s && !c)
		return ((char *)s);
	if (!*s)
		return ((char *)0);
	while (*s)
	{
		if (*s == (char)c)
			r = (char *)s;
		s++;
	}
	if (!*s && !c)
		return ((char *)s);
	return (r);
}
