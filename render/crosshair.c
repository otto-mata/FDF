/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crosshair.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 18:51:19 by tblochet          #+#    #+#             */
/*   Updated: 2024/12/20 19:10:37 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	set_crosshair(void)
{
	t_grid_node	*origin;
	t_engine	*engine;
	t_map_dim	*dim;

	engine = engine_instance();
	if (!engine)
		return ;
	origin = malloc(sizeof(t_grid_node));
	if (!origin)
		return ;
	origin->n_neighbors = 3;
	origin->neighbors = malloc((origin->n_neighbors + 1)
			* sizeof(t_grid_node *));
	if (!origin->neighbors)
		return ;
	origin->neighbors[0] = malloc(sizeof(t_grid_node));
	origin->neighbors[1] = malloc(sizeof(t_grid_node));
	origin->neighbors[2] = malloc(sizeof(t_grid_node));
	if (!origin->neighbors[0] || !origin->neighbors[1] || !origin->neighbors[2])
		return ;
	dim = malloc(sizeof(t_map_dim));
	if (!dim)
		return ;
	dim->height = 2;
	dim->width = 2;
	origin->color = 0xffffff;
	origin->coords = (t_vec3){0, 0, 0};
	origin->map_dim = dim;
	origin->neighbors[0]->map_dim = dim;
	origin->neighbors[1]->map_dim = dim;
	origin->neighbors[2]->map_dim = dim;
	origin->neighbors[0]->coords = (t_vec3){5, 0, 0};
	origin->neighbors[1]->coords = (t_vec3){0, 5, 0};
	origin->neighbors[2]->coords = (t_vec3){0, 0, -5};
	origin->neighbors[0]->color = 0xff0000;
	origin->neighbors[1]->color = 0x00ff00;
	origin->neighbors[2]->color = 0x0000ff;
	origin->neighbors[3] = 0;
	engine->crosshair = origin;
	origin->next = 0;
}
