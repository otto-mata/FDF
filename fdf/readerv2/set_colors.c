/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 01:11:27 by tblochet          #+#    #+#             */
/*   Updated: 2024/12/27 12:28:36 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readerv2.h"

static double	step(t_map_data *map, double z) __attribute__((unused));

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

static double	norm(t_map_data *map, double z)
{
	return ((z - map->lowest) / (map->highest - map->lowest));
}

static double	step(t_map_data *map, double z)
{
	const double	normal = norm(map, z);

	if (normal <= 0.125)
		return (0.125);
	if (normal <= 0.25)
		return (0.25);
	if (normal <= 0.375)
		return (0.375);
	if (normal <= 0.5)
		return (0.5);
	if (normal <= 0.625)
		return (0.625);
	if (normal <= 0.750)
		return (0.750);
	if (normal <= 0.875)
		return (0.875);
	return (1.0);
}

void	set_colors(t_map_data *map)
{
	int	color;

	map->iter = map->nodes;
	while (map->iter)
	{
		if (!map->iter->color)
		{
			color = c_lerp(0xff0000, 0x0000ff, norm(map, map->iter->coords.z));
			if (color)
				map->iter->color = color;
			else
				map->iter->color = 0xffffff;
		}
		map->iter = map->iter->next;
	}
}
