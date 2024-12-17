/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 04:00:16 by tblochet          #+#    #+#             */
/*   Updated: 2024/12/17 04:46:20 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READER_H
# define READER_H
# include <fcntl.h>
# include <sys/types.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_point_val	t_point_val;

struct						s_point_val
{
	int						height;
	int						color;
};

size_t						_strlen(char const *s);
char						**split(char const *s, char c);
void						*free_char2d(char **arr2d);
#endif