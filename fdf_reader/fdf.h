/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:57:24 by tblochet          #+#    #+#             */
/*   Updated: 2024/11/15 19:14:42 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <stdbool.h>
# include <fcntl.h>
# include <unistd.h>
# include "../get_next_line.h"
# include "../libft/libft.h"
# include "../otto/list.h"

typedef struct s_raw_data	t_raw_data;
typedef struct s_vec3		t_vec3;
typedef t_vec3				t_point3;


struct s_raw_data
{
	int			x;
	int			y;
	char		*parsed;
	int			len;

};

typedef struct s_fdf_file
{
	int			width;
	int			height;
	int			zmin;
	int			zmax;
	bool		has_colors;
	t_ottolist	*raw_data;
}				t_fdf_file;

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}				t_vec3;

typedef struct s_map3
{
	t_ottolist	*points;
	int			width;
	int			height;
	int			zmin;
	int			zmax;
}				t_map3;

t_fdf_file	*fdf_parse_file(char const *path);
t_map3		*fdf_convert_raw_data(t_fdf_file *file_data);

#endif