/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:21:19 by rleskine          #+#    #+#             */
/*   Updated: 2023/01/11 11:14:59 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE	64
#endif

t_line	*init_ln(int size, t_line *ln, char *new, int i)
{
	if (ln == NULL)
	{
		ln = (t_line *)malloc(sizeof(t_line));
		if (ln == NULL)
			return (NULL);
		ln->ln = NULL;
		ln->size = size / 2;
		ln->prev = NULL;
		ln->readsize = 0;
		ln->final = NULL;
		ln->pos = 0;
	}
	new = (char *)malloc(sizeof(char) * (ln->size * 2) + 1);
	if (new == NULL)
		return (NULL);
	while (i++ < ln->size && ln->ln != NULL)
		*(new + (i - 1)) = *(ln->ln + (i - 1));
	if (ln->ln != NULL)
		free(ln->ln);
	ln->ln = new;
	ln->size = (ln->size * 2);
	return (ln);
}

t_link	*init_node(int fd, t_link *node, t_line *ln)
{
	if (node == NULL && ln != NULL)
	{
		if (ln->prev != NULL && ln->node == (ln->node)->next)
			(ln->prev)->next = ln->prev;
		else if (ln->prev == NULL)
			ln->frst = (ln->node)->next;
		else
			(ln->prev)->next = (ln->node)->next;
		free((ln->node)->buf);
		free(ln->node);
	}
	node = (t_link *)malloc(sizeof(t_link));
	if (node == NULL)
		return (NULL);
	else if (ln == NULL)
		node->buf = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	if (node->buf == NULL || ln != NULL)
	{
		free(node);
		return (NULL);
	}
	node->fd = fd;
	node->size = 0;
	node->next = node;
	return (node);
}

t_link	*finalize(int fd, int find, t_line *ln)
{
	if (find == 1)
	{
		ln->prev = ln->frst;
		while (((t_link *)((ln->prev)->next))->fd != fd && \
				ln->prev != (ln->prev)->next)
			ln->prev = (ln->prev)->next;
		if (((t_link *)((ln->prev)->next))->fd != fd)
			((t_link *)(ln->prev))->next = init_node(fd, NULL, NULL);
		return ((t_link *)((ln->prev)->next));
	}
	if (ln->pos > 0)
		ln->final = (char *)malloc(sizeof(char) * (ln->pos + 1));
	if (ln->pos > 0 && ln->final == NULL)
		return (NULL);
	else if (ln->pos > 0)
		*(ln->final + ln->pos) = 0;
	if (ln->pos > 0)
		while (ln->pos-- > 0)
			*(ln->final + ln->pos) = *(ln->ln + ln->pos);
	if (ln->readsize < 1 && ln->node != NULL && (ln->node)->size < 1)
		init_node(0, NULL, ln);
	free(ln->ln);
	return (ln->node);
}

int	copy_next_line(t_line *ln, t_link *node)
{
	if (node->size == 0 && ln->readsize > -1)
	{
		ln->readsize = read(node->fd, node->buf, BUFFER_SIZE);
		(ln->node)->size = ln->readsize;
		(ln->node)->pos = (ln->node)->buf;
	}
	if (node->size < 1)
		return (0);
	while ((ln->size - ln->pos) < node->size)
		if (init_ln(0, ln, NULL, 0) == NULL)
			return (0);
	while (node->size > 0 && *(node->pos) != '\n')
	{
		if (*(node->pos) == 0)
			*(node->pos) = 'N';
		*(ln->ln + (ln->pos)++) = *(node->pos)++;
		node->size--;
	}
	if (node->size > 0 && *(node->pos) == '\n')
	{
		*(ln->ln + (ln->pos)++) = *(node->pos)++;
		node->size--;
		return (0);
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static t_link	*frst;
	t_line			*ln;
	char			*final;

	if (frst == NULL)
		frst = init_node(fd, NULL, NULL);
	ln = init_ln(12, NULL, NULL, 0);
	if (frst == NULL || ln == NULL)
		return (NULL);
	ln->frst = frst;
	if (frst->fd == fd)
		ln->node = frst;
	else
		ln->node = finalize(fd, 1, ln);
	while (copy_next_line(ln, ln->node))
		;
	if (fd == frst->fd && frst == frst->next && \
		ln->readsize < 1 && frst->size < 1)
		frst = NULL;
	finalize(fd, 0, ln);
	if (frst != NULL && frst != ln->frst)
		frst = ln->frst;
	final = ln->final;
	free(ln);
	return (final);
}
