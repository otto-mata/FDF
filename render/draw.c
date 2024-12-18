/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 00:51:01 by tblochet          #+#    #+#             */
/*   Updated: 2024/12/18 01:11:08 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	iswap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

bool	draw(int x, int y, int color)
{
	t_engine	*engine;

	engine = engine_instance();
	if (!engine)
		return (false);

	return (mlx_pixel_put(engine->mlx, engine->win, x, y, color));
}

static void	__gs_line_drw(t_ipoint __p, t_fpoint __d, int __tx, int __ty)
{
	while (__p.z--)
	{
		draw(__p.x, __p.y, 0xffffffff);
		if (__p.x < __tx)
			__p.x++;
		if (__d.z <= 0)
			__d.z += 2 * __d.y;
		else
		{
			__d.z += 2 * (__d.y - __d.x);
			if (__p.y < __ty)
				__p.y++;
		}
	}
}

bool	gs_line(t_ipoint p1, t_ipoint p2)
{
	float	dx;
	float	dy;
	float	d;
	int		x;
	int		y;

	if (p1.x > p2.x)
		iswap(&p1.x, &p2.x);
	if (p1.y > p2.y)
		iswap(&p1.y, &p2.y);
	x = p1.x;
	y = p1.y;
	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	d = 2 * (dy - dx);
	__gs_line_drw((t_ipoint){x, y, sqrt(dx * dx + dy * dy)}, (t_fpoint){dx, dy,
		d}, p2.x, p2.y);
	return (true);
}
