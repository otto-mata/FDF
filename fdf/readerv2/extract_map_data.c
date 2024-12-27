/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 23:16:37 by tblochet          #+#    #+#             */
/*   Updated: 2024/12/27 12:02:43 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readerv2.h"

static bool	populate_node(t_map_data *map, char *raw)
{
	char	**values;
	int		z_val;

	if (ft_strchr(raw, ','))
		values = ft_split(raw, ',');
	else
		values = ft_split(raw, 0);
	if (!values)
		return (false);
	if (ft_strchr(raw, ','))
		map->iter->color = ft_strtohl(values[1] + 2);
	else
		map->iter->color = 0;
	z_val = ft_atoi(values[0]) * -1;
	if (z_val > map->highest)
		map->highest = z_val;
	else if (z_val < map->lowest)
		map->lowest = z_val;
	map->iter->coords.z = z_val;
	map->iter->coords.x = map->parser->x;
	map->iter->coords.y = map->parser->y;
	map->iter->map_dim = map->dimensions;
	free_2d((void **)values);
	index_node(map->iter, map->parser->x, map->parser->y);
	return (true);
}

static int	iter_node(t_map_data *map, char **parts)
{
	if (!populate_node(map, parts[map->parser->x]))
		exit(EXIT_FAILURE);
	map->iter->next = ft_calloc(1, sizeof(t_grid_node));
	if (!map->iter->next)
		return (0);
	map->iter = map->iter->next;
	map->iter->map_dim = map->dimensions;
	return (1);
}

static int	parse_content(char const *content, t_map_data *map)
{
	char	**lines;
	char	**parts;

	lines = ft_split(content, '\n');
	if (!lines)
		return (0);
	map->parser->y = 0;
	while (lines[map->parser->y])
	{
		map->parser->x = 0;
		parts = ft_split(lines[map->parser->y], ' ');
		if (!parts)
			return (free_2d((void **)lines), 0);
		while (parts[map->parser->x])
		{
			iter_node(map, parts);
			map->parser->x++;
		}
		free_2d((void **)parts);
		map->parser->y++;
	}
	return (free_2d((void **)lines), 1);
}

t_map_data	*extract_map_data(char const *content)
{
	t_map_data	*map;

	map = ft_calloc(1, sizeof(t_map_data));
	if (!map)
		return (0);
	map->lowest = INT32_MAX;
	map->highest = INT32_MIN;
	map->dimensions = get_map_dimensions(content);
	if (!map->dimensions)
		return (free(map), (void *)0);
	init_index_table(map->dimensions);
	map->nodes = ft_calloc(1, sizeof(t_grid_node));
	if (!map->nodes)
		return (free(map), free(map->dimensions), (void *)0);
	map->iter = map->nodes;
	map->parser = ft_calloc(1, sizeof(t_parser));
	if (!map->parser)
		return (free(map), free(map->dimensions), free(map->nodes), (void *)0);
	if (!parse_content(content, map))
		return (free(map), free(map->dimensions), free(map->nodes),
			free(map->parser), (void *)0);
	if (!set_neighbors(map))
		return (0);
	set_colors(map);
	return (map);
}
