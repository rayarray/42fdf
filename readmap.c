/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 12:50:47 by rleskine          #+#    #+#             */
/*   Updated: 2023/05/24 14:52:03 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	*init_map(char *line)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (map == NULL)
		return (NULL);
	map->col = get_rowsize(line, 0);
	map->row = 1;
	map->pos = -1;
	return (map);
}

int	*parse_row(t_map *map, int *row, char *line, int x)
{
	row = (int *)malloc(sizeof(int) * map->col * 2);
	if (row == NULL)
		return (NULL);
	while (*line == ' ')
		line++;
	while (line != NULL && map->col > x)
	{
		line = parse_value(line, row, (row + map->col));
		update_minmax(map, *row);
		row++;
		(map->pos)++;
		x++;
	}
	row = row - map->pos;
	map->pos = 0;
	return (row);
}

void	parse_map(int *row, t_map *map, char *line)
{
	row = parse_row(map, NULL, line, 0);
	if (line != NULL)
		free(line);
	line = get_next_line(map->fd);
	if (line != NULL && *line != 0 && (map->row)++)
		parse_map(NULL, map, line);
	else
	{
		map->z = (int **)malloc(sizeof(int *) * map->row);
		map->rgb = (int **)malloc(sizeof(int *) * map->row);
		if (map->rgb == NULL && map->z != NULL)
			free(map->z);
		if (map->z == NULL && map->rgb != NULL)
			free(map->rgb);
		map->pos = map->row;
	}
	if ((map->z == NULL || map->rgb == NULL) && row != NULL)
		free(row);
	else
	{
		*(map->z + --(map->pos)) = row;
		*(map->rgb + map->pos) = row + map->col;
	}
}

t_map	*readmap(int fd)
{
	t_map	*map;
	char	*line;

	line = get_next_line(fd);
	map = init_map(line);
	if (map == NULL)
		return (NULL);
	map->fd = fd;
	if (map->col > 0)
		parse_map(NULL, map, line);
	return (map);
}
