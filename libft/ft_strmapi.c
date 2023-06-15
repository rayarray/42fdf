/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:11:37 by rleskine          #+#    #+#             */
/*   Updated: 2022/11/23 11:33:59 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*ret[2];
	unsigned int	index;

	if (f == NULL || s == NULL)
		return (NULL);
	ret[0] = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (ret[0] == NULL)
		return (NULL);
	ret[1] = ret[0];
	index = 0;
	while (*s)
	{
		*ret[0] = f(index, *s);
		ret[0]++;
		s++;
		index++;
	}
	*ret[0] = 0;
	return (ret[1]);
}
