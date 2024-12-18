/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 04:00:30 by tblochet          #+#    #+#             */
/*   Updated: 2024/12/18 12:50:05 by tblochet         ###   ########.fr       */
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

static t_map_dim	get_map_dimensions(char **lines)
{
	char		**parts;
	t_map_dim	dim;

	dim = (t_map_dim){0, 0};
	while (lines[dim.height])
		dim.height++;
	parts = split(lines[0], ' ');
	if (!parts)
		return ((t_map_dim){0, 0});
	while (parts[dim.width])
		dim.width++;
	free_char2d(parts);
	return (dim);
}

bool	populate_node(t_grid_node *node, char *raw)
{
	char	**values;

	if (strchr(raw, ','))
		values = split(raw, ',');
	else
		values = split(raw, 0);
	if (!values)
		return (false);
	if (strchr(raw, ','))
		node->color = strtol(values[1] + 2, 0, 16);
	else
		node->color = 0x0;
	node->coords.z = atoi(values[0]);
	free_char2d(values);
	return (true);
}

t_grid_node	*find_node_by_coords(t_grid_node *head, double x, double y)
{
	while (head)
	{
		if (head->coords.x == x && head->coords.y == y)
			return (head);
		head = head->next;
	}
	return (0);
}

t_grid_node	**set_neighbors(t_grid_node *node, t_map_dim dim, t_grid_node *head)
{
	t_grid_node	**neighbors;
	int			neighbors_count;

	neighbors_count = 0;
	if (node->coords.x > 0)
		neighbors_count++;
	if (node->coords.y > 0)
		neighbors_count++;
	if (node->coords.x < dim.width - 1)
		neighbors_count++;
	if (node->coords.y < dim.height - 1)
		neighbors_count++;
	neighbors = malloc((neighbors_count + 1) * sizeof(t_grid_node *));
	if (!neighbors)
		return (0);
	neighbors_count = 0;
	if (node->coords.x > 0)
		neighbors[neighbors_count++] = find_node_by_coords(head, node->coords.x
				- 1, node->coords.y);
	if (node->coords.y > 0)
		neighbors[neighbors_count++] = find_node_by_coords(head, node->coords.x,
				node->coords.y - 1);
	if (node->coords.x < dim.width - 1)
		neighbors[neighbors_count++] = find_node_by_coords(head, node->coords.x
				+ 1, node->coords.y);
	if (node->coords.y < dim.height - 1)
		neighbors[neighbors_count++] = find_node_by_coords(head, node->coords.x,
				node->coords.y + 1);
	neighbors[neighbors_count] = 0;
	node->neighbors = neighbors;
	return (neighbors);
}

t_grid_node	*extract_map_data(char *content)
{
	char		**lines;
	char		**line_parts;
	t_grid_node	*node;
	t_grid_node	*head;
	t_map_dim	dim;
	int			i;
	int			j;

	lines = split(content, '\n');
	if (!lines)
		return (0);
	dim = get_map_dimensions(lines);
	head = malloc(sizeof(t_grid_node));
	if (!head)
		return (0);
	i = -1;
	node = head;
	while (lines[++i])
	{
		line_parts = split(lines[i], ' ');
		if (!line_parts)
			return (free_char2d(lines));
		j = -1;
		while (line_parts[++j])
		{
			populate_node(node, line_parts[j]);
			node->coords.x = j;
			node->coords.y = i;
			node->next = malloc(sizeof(t_grid_node));
			if (!node->next)
				return (free_char2d(line_parts), free_char2d(lines));
			node = node->next;
		}
		free_char2d(line_parts);
	}
	node->next = 0;
	node = head;
	while (node)
	{
		node->neighbors = set_neighbors(node, dim, head);
		node = node->next;
	}
	free_char2d(lines);
	return (head);
}
#include <stdio.h>
t_grid_node	*map_nodes(void)
{
	char		*content;
	t_grid_node	*head;
	t_grid_node	*current;

	content = get_file_content("maps/elem.fdf");
	if (!content)
		return (0);
	head = extract_map_data(content);
	if (!head)
		return (0);
	free(content);
	current = head;
	while (current)
	{
		printf("Node at x: %f, y: %f, z: %f, color: %x\n", current->coords.x,
			current->coords.y, current->coords.z, current->color);
		current = current->next;
	}
	return (head);
}
