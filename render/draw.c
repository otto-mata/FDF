/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 00:51:01 by tblochet          #+#    #+#             */
/*   Updated: 2024/12/22 04:29:37 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int	c_lerp(int color1, int color2, double t)
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

bool	node_in_screen(t_grid_node n)
{
	t_engine	*engine;

	engine = engine_instance();
	if (!engine)
		return (false);
	return (n.coords.x >= 0 && n.coords.x <= engine->config.width
		&& n.coords.y >= 0 && n.coords.y <= engine->config.height);
}

bool	draw(t_grid_node p)
{
	t_engine	*engine;
	int			offset;

	engine = engine_instance();
	if (!engine)
		exit(EXIT_FAILURE);
	offset = ((int)p.coords.y * engine->img->line_length) + ((int)p.coords.x
			* (engine->img->bpp >> 3));
	if (offset >= 0 && offset < (engine->img->line_length
			* engine->config.height) && node_in_screen(p))
		*(int *)(engine->img->data + offset) = p.color;
	return (true);
}

static t_vec3	proj(t_grid_node p)
{
	t_vec3		v;
	t_engine	*engine;

	engine = engine_instance();
	if (!engine)
		exit(EXIT_FAILURE);
	p.coords.x *= engine->zoom;
	p.coords.y *= engine->zoom;
	p.coords.z *= engine->zoom;
	p.coords.x -= ((int)(p.map_dim->width * engine->zoom)) >> 1;
	p.coords.y -= ((int)(p.map_dim->height * engine->zoom)) >> 1;
	v.x = engine->origin[0].x * p.coords.x + engine->origin[1].x * p.coords.y
		+ engine->origin[2].x * p.coords.z;
	v.y = engine->origin[0].y * p.coords.x + engine->origin[1].y * p.coords.y
		+ engine->origin[2].y * p.coords.z;
	v.z = engine->origin[0].z * p.coords.x + engine->origin[1].z * p.coords.y
		+ engine->origin[2].z * p.coords.z;
	v.x += (engine->config.width >> 1) + engine->offset_x;
	v.y += (engine->config.height >> 1) + engine->offset_y;
	return (v);
}

bool	gs_line(t_grid_node *p1, t_grid_node *p2)
{
	t_vec3		delta;
	double		steps;
	t_vec3		step;
	t_grid_node	target;
	int			i;
	t_engine	*engine;

	engine = engine_instance();
	if (!engine)
		return (false);
	delta.x = (proj(*p2).x - proj(*p1).x);
	delta.y = (proj(*p2).y - proj(*p1).y);
	delta.z = (proj(*p2).z - proj(*p1).z);
	steps = fmax(fabs(delta.x), fmax(fabs(delta.y), fabs(delta.z)));
	step.x = delta.x / steps;
	step.y = delta.y / steps;
	step.z = delta.z / steps;
	target.coords.x = proj(*p1).x;
	target.coords.y = proj(*p1).y;
	target.coords.z = proj(*p1).z;
	target.map_dim = p1->map_dim;
	for (i = 0; i <= steps; i++)
	{
		target.color = c_lerp(p1->color, p2->color, (double)i / steps);
		draw(target);
		target.coords.x += step.x;
		target.coords.y += step.y;
	}
	return (true);
}
