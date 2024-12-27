/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readerv2.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 20:53:38 by tblochet          #+#    #+#             */
/*   Updated: 2024/12/27 01:17:00 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READERV2_H
# define READERV2_H
# include "../../libft/libft.h"
# include "../../vec3/vec3.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>

typedef struct s_map_data		t_map_data;
typedef struct s_map_dim		t_map_dim;
typedef struct s_grid_node		t_grid_node;
typedef struct s_index_table	t_index_table;
typedef struct s_parser			t_parser;

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
struct							s_parser
{
	int							x;
	int							y;
};

struct							s_map_data
{
	int							lowest;
	int							highest;
	t_grid_node					*nodes;
	t_grid_node					*iter;
	t_map_dim					*dimensions;
	t_parser					*parser;
};

ssize_t							get_file_size(char const *path);
char							*get_file_content(char const *path);
void							*free_2d(void **arr2d);
size_t							arrlen(void **arr);
void							index_node(t_grid_node *node, int x, int y);
void							init_index_table(t_map_dim *dimensions);
t_index_table					*get_index_table(void);
t_map_dim						*get_map_dimensions(char const *content);
int								set_neighbors(t_map_data *map);
t_map_data						*load_map(char const *path);
t_map_data						*extract_map_data(char const *content);
void							set_colors(t_map_data *map);
#endif