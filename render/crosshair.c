/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crosshair.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 18:51:19 by tblochet          #+#    #+#             */
/*   Updated: 2024/12/21 17:02:42 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

t_vec3	apply_projection(t_grid_node *p)
{
	t_vec3		v;
	t_engine	*engine;

	engine = engine_instance();
	if (!engine)
		exit(EXIT_FAILURE);
	v.x = p->coords.x;
	v.y = p->coords.y;
	v.z = p->coords.z;
	rot_x(&v.y, &v.z, engine->rot_x);
	rot_y(&v.x, &v.z, engine->rot_y);
	rot_z(&v.x, &v.y, engine->rot_z);
	v.z = 0;
	return (v);
}

void	set_crosshair(void)
{
	t_grid_node	*origin;
	t_engine	*engine;
	t_map_dim	*dim;

	engine = engine_instance();
	if (!engine)
		exit(EXIT_FAILURE);
	origin = malloc(sizeof(t_grid_node));
	if (!origin)
		return ;
	dim = malloc(sizeof(t_map_dim));
	if (!dim)
		return ;
	dim->height = 2;
	dim->width = 2;
	origin->color = 0xffffff;
	origin->map_dim = dim;
	origin->coords = (t_vec3){1, 0, 0};
	engine->origin[0] = apply_projection(origin);
	origin->coords = (t_vec3){0, 1, 0};
	engine->origin[1] = apply_projection(origin);
	origin->coords = (t_vec3){0, 0, 1};
	engine->origin[2] = apply_projection(origin);
	return (free(dim), free(origin));
}
