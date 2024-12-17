/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 04:00:30 by tblochet          #+#    #+#             */
/*   Updated: 2024/12/17 05:29:35 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

static ssize_t	get_file_size(char const *path)
{
	ssize_t	sz;
	ssize_t	inc;
	int		fd;
	char	buf[1024];

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	if (read(fd, 0, 0) < 0)
		return (-1);
	sz = 0;
	inc = 1;
	while (inc > 0)
	{
		inc = read(fd, buf, 1024);
		if (inc > 0)
			sz += inc;
	}
	return (sz);
}

char	*get_file_content(char const *path)
{
	int		fd;
	ssize_t	file_size;
	char	*content;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	if (read(fd, 0, 0) < 0)
		return (0);
	file_size = get_file_size(path);
	if (file_size < 0)
		return (0);
	content = malloc((file_size + 1) * sizeof(char));
	if (!content)
		return (0);
	content[file_size] = 0;
	if (read(fd, content, file_size) < 0)
		return (free(content), (char *)0);
	return (content);
}

static ssize_t	get_point_count(char **lines)
{
	char	**parts;
	int		i;
	int		j;
	ssize_t	sz;

	i = 0;
	sz = 0;
	while (lines[i])
	{
		parts = split(lines[i], ' ');
		if (!parts)
			return (-1);
		j = 0;
		while (parts[j++])
			sz++;
		free_char2d(parts);
		parts = 0;
		i++;
	}
	return (sz);
}

void	*populate_tab(t_point_val **tab, char *raw)
{
	static int	i = 0;
	char		**values;

	if (strchr(raw, ','))
		values = split(raw, ',');
	else
		values = split(raw, 0);
	if (!values)
		return (0);
	tab[i] = malloc(sizeof(t_point_val));
	if (!tab[i])
		return (0);
	tab[i]->color = 0;
	tab[i]->height = atoi(values[0]);
	free_char2d(values);
	i++;
	tab[i] = 0;
	return ((void *)1);
}

t_point_val	**extract_map_data(char *content)
{
	char		**lines;
	char		**line_parts;
	t_point_val	**points;
	int			i;
	int			j;

	lines = split(content, '\n');
	if (!lines)
		return (0);
	points = malloc((get_point_count(lines) + 1) * sizeof(t_point_val *));
	if (!points)
		return (0);
	i = -1;
	while (lines[++i])
	{
		line_parts = split(lines[i], ' ');
		if (!line_parts)
			return (free_char2d(lines));
		j = 0;
		while (line_parts[j])
			populate_tab(points, line_parts[j++]);
		free_char2d(line_parts);
	}
	free_char2d(lines);
	return (points);
}

#include <stdio.h>
int	main(void)
{
	char		*content;
	t_point_val	**pts;

	content = get_file_content("./maps/elem-col.fdf");
	if (!content)
		return (1);
	pts = extract_map_data(content);
	if (!pts)
		return (2);
	while (*pts)
	{
		printf("h: %d, c: %d\n", (*pts)->height, (*pts)->color);
		pts++;
	}
	free(content);
	// free_char2d((char **)pts);
	return (0);
}
