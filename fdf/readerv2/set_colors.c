/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 01:11:27 by tblochet          #+#    #+#             */
/*   Updated: 2024/12/27 01:24:59 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readerv2.h"

static int	c_lerp(int color1, int color2, double t)
{
	int	r;
	int	g;
	int	b;

	r = (int)(((color1 >> 16) & 0xFF) + t * (((color2 >> 16) & 0xFF)
				- ((color1 >> 16) & 0xFF)));
	g = (int)(((color1 >> 8) & 0xFF) + t * (((color2 >> 8) & 0xFF)
				- ((color1 >> 8) & 0xFF)));
	b = (int)((color1 & 0xFF) + t * ((color2 & 0xFF) - (color1 & 0xFF)));
	return ((r << 16) | (g << 8) | b);
}

static double	normalize(t_map_data *map, double z)
{
	return ((z - map->lowest) / (map->highest - map->lowest));
}

void	set_colors(t_map_data *map)
{
	int	color;

	map->iter = map->nodes;
	while (map->iter)
	{
		if (!map->iter->color)
		{
			color = c_lerp(0xff0000, 0x0000ff, normalize(map,
						map->iter->coords.z));
			if (color)
				map->iter->color = color;
			else
				map->iter->color = 0xffffff;
		}
		map->iter = map->iter->next;
	}
}
