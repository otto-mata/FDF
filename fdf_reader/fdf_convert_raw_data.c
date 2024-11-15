/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_convert_raw_data.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 18:24:25 by tblochet          #+#    #+#             */
/*   Updated: 2024/11/15 18:38:34 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map3	*fdf_convert_raw_data(t_fdf_file *file_data)
{
	t_map3		*mapped;
	t_raw_data	*raw_point;
	t_point3	*point;
	t_ottolist	*raw_data;
	int			i;

	mapped = ft_calloc(1, sizeof(t_map3));
	if (!mapped)
		return (0);
	mapped->points = list_new();
	point = ft_calloc(1, sizeof(t_point3));
	raw_data = file_data->raw_data;
	i = 0;
	while (i < raw_data->len)
	{
		raw_point = raw_data->content[i];
		point->x = raw_point->x;
		point->y = raw_point->y;
		point->z = ft_atoi(raw_point->parsed);
		list_append(point, &(mapped->points));
		point = ft_calloc(1, sizeof(t_point3));
		i++;
	}
	return (mapped);
}
