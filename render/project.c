/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 00:56:50 by tblochet          #+#    #+#             */
/*   Updated: 2024/12/18 11:45:14 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	rot_x(double *y, double *z, double angle)
{
	double	prev_y;
	double	rad;

	rad = (angle) * (PI / 180);
	prev_y = *y;
	*y = prev_y * cos(rad) + *z * sin(rad);
	*z = prev_y * -sin(rad) + *z * cos(rad);
}

void	rot_y(double *x, double *z, double angle)
{
	double	prev_x;
	double	rad;

	rad = (angle) * (PI / 180);
	prev_x = *x;
	*x = prev_x * cos(rad) + *z * sin(rad);
	*z = prev_x * -sin(rad) + *z * cos(rad);
}

void	rot_z(double *x, double *y, double angle)
{
	t_point prev;
	double rad;

	rad = (angle) * (PI / 180);
	prev.x = *x;
	prev.y = *y;
	*x = prev.x * cos(rad) - prev.y * sin(rad);
	*y = prev.x * sin(rad) + prev.y * cos(rad);
}
