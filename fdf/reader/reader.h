/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 04:00:16 by tblochet          #+#    #+#             */
/*   Updated: 2024/12/18 10:28:59 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READER_H
# define READER_H
# include <fcntl.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <unistd.h>

typedef struct s_map_dim	t_map_dim;
typedef struct s_grid_node	t_grid_node;

# ifndef STRUCT_POINT
#  define STRUCT_POINT

typedef struct s_point		t_point;
struct						s_point
{
	double					x;
	double					y;
	double					z;
};
# endif

struct						s_map_dim
{
	int						width;
	int						height;
};

struct						s_grid_node
{
	int						color;
	t_point					coords;
	t_grid_node				**neighbors;
	t_grid_node				*next;
};

size_t						_strlen(char const *s);
char						**split(char const *s, char c);
void						*free_char2d(char **arr2d);
t_grid_node					*map_nodes(void);
#endif