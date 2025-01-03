/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   crosshair.c                                          ┌─┐┌┬┐┌┬┐┌─┐        */
/*                                                        │ │ │  │ │ │        */
/*   By: tblochet <tblochet@student.42.fr>                └─┘ ┴  ┴ └─┘        */
/*                                                        ┌┬┐┌─┐┌┬┐┌─┐        */
/*   Created: 2024/12/20 18:51:19 by tblochet             │││├─┤ │ ├─┤        */
/*   Updated: 2025/01/03 02:42:27 by tblochet             ┴ ┴┴ ┴ ┴ ┴ ┴        */
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

static t_vec3	vec3_stack_from(int x, int y, int z)
{
	t_vec3	v;

	v.x = x;
	v.y = y;
	v.z = z;
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
	origin->coords = vec3_stack_from(1, 0, 0);
	engine->origin[0] = apply_projection(origin);
	origin->coords = vec3_stack_from(0, 1, 0);
	engine->origin[1] = apply_projection(origin);
	origin->coords = vec3_stack_from(0, 0, 1);
	engine->origin[2] = apply_projection(origin);
	free(dim);
	free(origin);
}
