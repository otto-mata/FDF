/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:57:24 by tblochet          #+#    #+#             */
/*   Updated: 2024/11/15 13:22:34 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <stdbool.h>
# include <fcntl.h>
# include <unistd.h>
# include "../get_next_line.h"
# include "../libft/libft.h"

typedef struct s_raw_data	t_raw_data;

struct s_raw_data
{
	int			x;
	int			y;
	char		*parsed;
	int			len;
	t_raw_data	*next;

};

typedef struct s_fdf_file
{
	int		width;
	int		height;
	int		zmin;
	int		zmax;
	bool	has_colors;
	t_list	*raw_data;
}				t_fdf_file;

t_fdf_file	*fdf_parse_file(char const *path);

#endif