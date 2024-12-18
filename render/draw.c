/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 00:51:01 by tblochet          #+#    #+#             */
/*   Updated: 2024/12/18 12:58:15 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	dswap(double *a, double *b)
{
	double	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

bool	draw(double x, double y, double z, int color)
{
	t_engine	*engine;

	(void)z;
	engine = engine_instance();
	if (!engine)
		return (false);
	// rot_x(&y, &z, engine->rot_x);
	// rot_y(&x, &z, engine->rot_y);
	// rot_z(&x, &y, engine->rot_z);
	x += WIDTH / 2;
	y += HEIGHT / 2;
	// printf("Drawing (%.0f, %.0f)\n",x, y);
	return (mlx_pixel_put(engine->mlx, engine->win, x, y, color));
}

static void	__gs_line_drw(t_point __p, t_point __d, t_point __t)
{
	while (__p.z--)
	{
		draw(__p.x, __p.y, __t.z, 0xffffffff);
		if (__p.x < __t.x)
			__p.x++;
		if (__d.z <= 0)
			__d.z += 2 * __d.y;
		else
		{
			__d.z += 2 * (__d.y - __d.x);
			if (__p.y < __t.y)
				__p.y++;
		}
	}
}

bool	gs_line(t_point p1, t_point p2)
{
	double		dx;
	double		dy;
	double		d;
	double		x;
	double		y;
	t_engine	*engine;

	engine = engine_instance();
	if (!engine)
		return (false);
	rot_x(&p1.y, &p1.z, engine->rot_x);
	rot_y(&p1.x, &p1.z, engine->rot_y);
	rot_z(&p1.x, &p1.y, engine->rot_z);
	rot_x(&p2.y, &p2.z, engine->rot_x);
	rot_y(&p2.x, &p2.z, engine->rot_y);
	rot_z(&p2.x, &p2.y, engine->rot_z);
	if (p1.x > p2.x)
		dswap(&p1.x, &p2.x);
	if (p1.y > p2.y)
		dswap(&p1.y, &p2.y);
	x = p1.x;
	y = p1.y;
	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	d = 2 * (dy - dx);
	__gs_line_drw((t_point){x, y, floor(sqrt(dx * dx + dy * dy))}, (t_point){dx,
		dy, d}, (t_point){p2.x, p2.y, p2.z});
	return (true);
}
