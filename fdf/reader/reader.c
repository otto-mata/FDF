/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 04:00:30 by tblochet          #+#    #+#             */
/*   Updated: 2024/12/23 19:10:29 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

static t_index_table	*get_index_table(void)
{
	static t_index_table	*table = 0;

	if (!table)
	{
		table = calloc(1, sizeof(t_index_table));
		if (!table)
			exit(EXIT_FAILURE);
	}
	return (table);
}

static void	init_index_table(t_map_dim *dimensions)
{
	t_index_table *const	table = get_index_table();
	int						i;

	table->height = dimensions->height;
	table->width = dimensions->width;
	table->nodes = calloc((table->height + 1), sizeof(t_grid_node ***));
	i = 0;
	while (i < table->height)
		table->nodes[i++] = calloc(table->width + 1, sizeof(t_grid_node **));
	if (!table->nodes)
		exit(EXIT_FAILURE);
}

static void	index_node(t_grid_node *node, int x, int y)
{
	t_index_table *const	table = get_index_table();

	table->nodes[y][x] = node;
}

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

static t_map_dim	*get_map_dimensions(char **lines)
{
	char		**parts;
	t_map_dim	*dim;

	dim = calloc(1, sizeof(t_map_dim));
	if (!dim)
		return (0);
	while (lines[dim->height])
		dim->height++;
	parts = split(lines[0], ' ');
	if (!parts)
		return (0);
	while (parts[dim->width])
		dim->width++;
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
		node->color = 0;
	node->coords.z = atoi(values[0]) * -1;
	free_char2d(values);
	if (node->color)
		return (true);
	if (node->coords.z >= 0)
		node->color = 0x1a2e69;
	else if (node->coords.z >= -3)
		node->color = 0x416be8;
	else if (node->coords.z >= -7)
		node->color = 0x41dae8;
	else if (node->coords.z >= -10)
		node->color = 0xe87041;
	else
		node->color = 0xb9e841;
	return (true);
}

t_grid_node	*find_node_by_coords(int x, int y)
{
	t_index_table *const	table = get_index_table();

	return (table->nodes[y][x]);
}

t_grid_node	**set_neighbors(t_grid_node *node)
{
	t_grid_node	**neighbors;
	int			neighbors_count;

	neighbors_count = 0;
	if (node->coords.x < node->map_dim->width - 1)
		neighbors_count++;
	if (node->coords.y < node->map_dim->height - 1)
		neighbors_count++;
	neighbors = malloc((neighbors_count + 1) * sizeof(t_grid_node *));
	if (!neighbors)
		return (0);
	neighbors_count = 0;
	if (node->coords.x < node->map_dim->width - 1)
		neighbors[neighbors_count++] = find_node_by_coords(
				(int)floor(node->coords.x + 1), (int)floor(node->coords.y));
	if (node->coords.y < node->map_dim->height - 1)
		neighbors[neighbors_count++] = find_node_by_coords(
				(int)floor(node->coords.x), (int)floor(node->coords.y + 1));
	neighbors[neighbors_count] = 0;
	node->neighbors = neighbors;
	node->n_neighbors = neighbors_count;
	return (neighbors);
}

t_grid_node	*extract_map_data(char *content)
{
	char		**lines;
	char		**line_parts;
	t_grid_node	*node;
	t_grid_node	*head;
	t_map_dim	*dim;
	int			i;
	int			j;
	int			n;

	lines = split(content, '\n');
	if (!lines)
		return (0);
	dim = get_map_dimensions(lines);
	if (!dim)
		return (0);
	init_index_table(dim);
	head = malloc(sizeof(t_grid_node));
	if (!head)
		return (0);
	i = -1;
	node = head;
	while (lines[++i])
	{
		ft_printf("\rLine %d/%d done.", i + 1, dim->height);
		line_parts = split(lines[i], ' ');
		if (!line_parts)
			return (free_char2d(lines));
		j = -1;
		while (line_parts[++j])
		{
			populate_node(node, line_parts[j]);
			node->coords.x = j;
			node->coords.y = i;
			index_node(node, j, i);
			node->next = calloc(1, sizeof(t_grid_node));
			if (!node->next)
				return (free_char2d(line_parts), free_char2d(lines));
			node = node->next;
		}
		free_char2d(line_parts);
	}
	ft_printf("\nDone\n");
	node->next = 0;
	node = head;
	n = 0;
	while (node)
	{
		ft_printf("\rSetting node neighbors %d/%d", n, i * j);
		node->map_dim = dim;
		node->neighbors = set_neighbors(node);
		node = node->next;
		n++;
	}
	ft_printf("\nDone setting neighbors\n");
	free_char2d(lines);
	return (head);
}

t_grid_node	*map_nodes(char const *path)
{
	char				*content;
	t_grid_node			*head;
	int					i;
	t_index_table		*table;

	content = get_file_content(path);
	if (!content)
		return (0);
	head = extract_map_data(content);
	if (!head)
		return (0);
	table = get_index_table();
	i = 0;
	while (table->nodes[i])
		free(table->nodes[i++]);
	free(table->nodes);
	free(table);
	free(content);
	return (head);
}
