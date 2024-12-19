/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 00:51:01 by tblochet          #+#    #+#             */
/*   Updated: 2024/12/19 05:20:34 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

/* static void	dswap(double *a, double *b)
{
	double	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
} */

bool	draw(double x, double y, double z, int color)
{
	t_engine	*engine;

	engine = engine_instance();
	if (!engine)
		return (false);
	rot_x(&y, &z, engine->rot_x);
	rot_y(&x, &z, engine->rot_y);
	rot_z(&x, &y, engine->rot_z);
	x += WIDTH / 2;
	y += HEIGHT / 2;
	// printf("Drawing (%.0f, %.0f, %.0f)\n",x, y, z);
	return (mlx_pixel_put(engine->mlx, engine->win, x, y, color));
}

bool	gs_line(t_point p1, t_point p2)
{
	double	dx;
	double	dy;
	double	dz;
	double	steps;
	double	x_inc;
	double	y_inc;
	double	z_inc;
	double	x;
	double	y;
	double	z;
	int		i;

	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	dz = p2.z - p1.z;
	steps = fmax(fabs(dx), fmax(fabs(dy), fabs(dz)));
	x_inc = dx / steps;
	y_inc = dy / steps;
	z_inc = dz / steps;
	x = p1.x;
	y = p1.y;
	z = p1.z;
	for (i = 0; i <= steps; i++)
	{
		draw(x, y, z, 0xffffffff);
		x += x_inc;
		y += y_inc;
		z += z_inc;
	}
	return (true);
}