/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   vec3_ip_mult_scalar.c                                ┌─┐┌┬┐┌┬┐┌─┐        */
/*                                                        │ │ │  │ │ │        */
/*   By: tblochet <tblochet@student.42.fr>                └─┘ ┴  ┴ └─┘        */
/*                                                        ┌┬┐┌─┐┌┬┐┌─┐        */
/*   Created: 2024/12/01 01:36:06 by tblochet             │││├─┤ │ ├─┤        */
/*   Updated: 2025/01/03 02:42:13 by tblochet             ┴ ┴┴ ┴ ┴ ┴ ┴        */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

void	vec3_ip_mult_scalar(t_vec3 *v, double t)
{
	v->x *= t;
	v->y *= t;
	v->z *= t;
}
