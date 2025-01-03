/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   set_neighbors.c                                      ┌─┐┌┬┐┌┬┐┌─┐        */
/*                                                        │ │ │  │ │ │        */
/*   By: tblochet <tblochet@student.42.fr>                └─┘ ┴  ┴ └─┘        */
/*                                                        ┌┬┐┌─┐┌┬┐┌─┐        */
/*   Created: 2024/12/27 00:11:47 by tblochet             │││├─┤ │ ├─┤        */
/*   Updated: 2025/01/03 02:42:42 by tblochet             ┴ ┴┴ ┴ ┴ ┴ ┴        */
/*                                                                            */
/* ************************************************************************** */

#include "readerv2.h"

static t_grid_node	*get_by_index(double x, double y)
{
	const int			ix = (int)x;
	const int			iy = (int)y;
	const t_index_table	*table = get_index_table();

	return (table->nodes[iy][ix]);
}

static int	set_node_neighbors(t_grid_node *node)
{
	t_grid_node	**neighbors;
	int			n;

	n = 0;
	if (node->coords.x < node->map_dim->width - 1)
		n++;
	if (node->coords.y < node->map_dim->height - 1)
		n++;
	neighbors = ft_calloc((n + 1), sizeof(t_grid_node *));
	if (!neighbors)
		return (0);
	n = 0;
	if (node->coords.x < node->map_dim->width - 1)
		neighbors[n++] = get_by_index(node->coords.x + 1, node->coords.y);
	if (node->coords.y < node->map_dim->height - 1)
		neighbors[n++] = get_by_index(node->coords.x, node->coords.y + 1);
	neighbors[n] = 0;
	node->neighbors = neighbors;
	node->n_neighbors = n;
	return (1);
}

int	set_neighbors(t_map_data *map)
{
	map->iter = map->nodes;
	while (map->iter)
	{
		if (!set_node_neighbors(map->iter))
			return (0);
		map->iter = map->iter->next;
	}
	return (1);
}
