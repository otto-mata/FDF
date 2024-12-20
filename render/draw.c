/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 00:51:01 by tblochet          #+#    #+#             */
/*   Updated: 2024/12/20 11:42:46 by tblochet         ###   ########.fr       */
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
		return (false);
	p.coords.x -= p.map_dim->width * engine->zoom / 2;
	p.coords.y -= p.map_dim->height * engine->zoom / 2;
	rot_x(&p.coords.y, &p.coords.z, engine->rot_x);
	rot_y(&p.coords.x, &p.coords.z, engine->rot_y);
	rot_z(&p.coords.x, &p.coords.y, engine->rot_z);
	p.coords.x += WIDTH / 2;
	p.coords.y += HEIGHT / 2;
	offset = ((int)p.coords.y * engine->img->line_length) + ((int)p.coords.x
			* (engine->img->bits_per_pixel / 8));
	if (offset >= 0 && offset < (engine->img->line_length
			* engine->config.height) && node_in_screen(p))
		*(int *)(engine->img->addr + offset) = p.color;
	return (true);
}

bool	gs_line(t_grid_node *p1, t_grid_node *p2)
{
	t_point		delta;
	double		steps;
	t_point		step;
	t_grid_node	target;
	int			i;
	t_engine	*engine;

	engine = engine_instance();
	if (!engine)
		return (false);
	delta.x = p2->coords.x * engine->zoom - p1->coords.x * engine->zoom;
	delta.y = p2->coords.y * engine->zoom - p1->coords.y * engine->zoom;
	delta.z = p2->coords.z - p1->coords.z;
	steps = fmax(fabs(delta.x), fmax(fabs(delta.y), fabs(delta.z)));
	step.x = delta.x / steps;
	step.y = delta.y / steps;
	step.z = delta.z / steps;
	target.coords.x = p1->coords.x * engine->zoom;
	target.coords.y = p1->coords.y * engine->zoom;
	target.coords.z = p1->coords.z;
	target.map_dim = p1->map_dim;
	for (i = 0; i <= steps; i++)
	{
		target.color = c_lerp(p1->color, p2->color, (double)i / steps);
		draw(target);
		target.coords.x += step.x;
		target.coords.y += step.y;
		target.coords.z += step.z;
	}
	return (true);
}
