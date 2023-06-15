/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:02:36 by rleskine          #+#    #+#             */
/*   Updated: 2022/11/29 10:28:21 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	void			*ret;
	unsigned char	*ptr;
	size_t			bytes;

	bytes = count * size;
	if (count > 0 && size > 0)
		if (bytes % count != 0 || bytes % size != 0)
			return (NULL);
	ptr = (unsigned char *)malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	ret = (void *)ptr;
	while (bytes > 0)
	{
		*ptr = (unsigned char)0;
		ptr++;
		bytes--;
	}
	return (ret);
}
