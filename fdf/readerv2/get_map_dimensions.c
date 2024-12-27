/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_dimensions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 23:28:55 by tblochet          #+#    #+#             */
/*   Updated: 2024/12/27 00:24:38 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readerv2.h"

t_map_dim	*get_map_dimensions(char const *content)
{
	char		**parts;
	char		**lines;
	t_map_dim	*dim;

	dim = ft_calloc(1, sizeof(t_map_dim));
	if (!dim)
		return (0);
	lines = ft_split(content, '\n');
	if (!lines)
		return (free(dim), (void *)0);
	dim->height = arrlen((void **)lines);
	parts = ft_split(lines[0], ' ');
	if (!parts)
		return (free(dim), free_2d((void **)lines), (void *)0);
	dim->width = arrlen((void **)parts);
	free_2d((void **)parts);
	free_2d((void **)lines);
	return (dim);
}
