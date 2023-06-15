/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 09:58:45 by rleskine          #+#    #+#             */
/*   Updated: 2023/01/09 14:19:16 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

typedef struct s_link
{
	int		fd;
	int		size;
	void	*next;
	char	*pos;
	char	*buf;
}	t_link;

typedef struct s_line
{
	char	*ln;
	char	*final;
	int		size;
	int		pos;
	int		readsize;
	t_link	*prev;
	t_link	*node;
	t_link	*frst;
}	t_line;

char	*get_next_line(int fd);

#endif /* GET_NEXT_LINE_H */
