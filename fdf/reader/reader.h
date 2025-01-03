/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   reader.h                                             ┌─┐┌┬┐┌┬┐┌─┐        */
/*                                                        │ │ │  │ │ │        */
/*   By: tblochet <tblochet@student.42.fr>                └─┘ ┴  ┴ └─┘        */
/*                                                        ┌┬┐┌─┐┌┬┐┌─┐        */
/*   Created: 2024/12/17 04:00:16 by tblochet             │││├─┤ │ ├─┤        */
/*   Updated: 2025/01/03 02:42:47 by tblochet             ┴ ┴┴ ┴ ┴ ┴ ┴        */
/*                                                                            */
/* ************************************************************************** */

#ifndef READER_H
# define READER_H
# include "../../ft_printf/ft_printf.h"
# include "../../vec3/vec3.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <unistd.h>

typedef struct s_map_dim		t_map_dim;
typedef struct s_grid_node		t_grid_node;
typedef struct s_index_table	t_index_table;
struct							s_map_dim
{
	int							width;
	int							height;
};

struct							s_index_table
{
	int							width;
	int							height;
	t_grid_node					***nodes;
};

struct							s_grid_node
{
	int							color;
	t_vec3						coords;
	t_grid_node					**neighbors;
	t_grid_node					*next;
	t_map_dim					*map_dim;
	int							n_neighbors;
};

size_t							_strlen(char const *s);
char							**split(char const *s, char c);
void							*free_char2d(char **arr2d);
t_grid_node						*map_nodes(char const *fdf_file_path);
t_grid_node						*find_node_by_coords(int x, int y);
#endif