/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_dot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 01:48:25 by tblochet          #+#    #+#             */
/*   Updated: 2024/12/01 01:49:24 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

double	vec3_dot(t_vec3 *u, t_vec3 *v)
{
	return ((u->x * v->x) + (u->y * v->y) + (u->z * v->z));
}
