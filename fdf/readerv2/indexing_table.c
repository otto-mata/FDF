/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indexing_table.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 23:26:52 by tblochet          #+#    #+#             */
/*   Updated: 2024/12/26 23:27:59 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readerv2.h"

t_index_table	*get_index_table(void)
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

void	init_index_table(t_map_dim *dimensions)
{
	t_index_table	*table;
	int				i;

	table = get_index_table();
	table->height = dimensions->height;
	table->width = dimensions->width;
	table->nodes = calloc((table->height + 1), sizeof(t_grid_node ***));
	i = 0;
	while (i < table->height)
		table->nodes[i++] = calloc(table->width + 1, sizeof(t_grid_node **));
	if (!table->nodes)
		exit(EXIT_FAILURE);
}

void	index_node(t_grid_node *node, int x, int y)
{
	t_index_table	*table;

	table = get_index_table();
	table->nodes[y][x] = node;
}
