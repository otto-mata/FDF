/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   load_map.c                                           ┌─┐┌┬┐┌┬┐┌─┐        */
/*                                                        │ │ │  │ │ │        */
/*   By: tblochet <tblochet@student.42.fr>                └─┘ ┴  ┴ └─┘        */
/*                                                        ┌┬┐┌─┐┌┬┐┌─┐        */
/*   Created: 2024/12/27 00:20:34 by tblochet             │││├─┤ │ ├─┤        */
/*   Updated: 2025/01/03 02:42:40 by tblochet             ┴ ┴┴ ┴ ┴ ┴ ┴        */
/*                                                                            */
/* ************************************************************************** */

#include "readerv2.h"

t_map_data	*load_map(char const *path)
{
	char			*content;
	t_map_data		*map;
	int				i;
	t_index_table	*table;

	content = get_file_content(path);
	if (!content)
		return (free(content), (void *)0);
	map = extract_map_data(content);
	if (!map)
		return (0);
	table = get_index_table();
	i = 0;
	while (table->nodes[i])
		free(table->nodes[i++]);
	free(table->nodes);
	free(table);
	free(content);
	free(map->parser);
	map->parser = 0;
	map->iter = map->nodes;
	return (map);
}
