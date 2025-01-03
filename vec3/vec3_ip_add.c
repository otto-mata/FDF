/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   vec3_ip_add.c                                        ┌─┐┌┬┐┌┬┐┌─┐        */
/*                                                        │ │ │  │ │ │        */
/*   By: tblochet <tblochet@student.42.fr>                └─┘ ┴  ┴ └─┘        */
/*                                                        ┌┬┐┌─┐┌┬┐┌─┐        */
/*   Created: 2024/12/01 01:33:40 by tblochet             │││├─┤ │ ├─┤        */
/*   Updated: 2025/01/03 02:42:12 by tblochet             ┴ ┴┴ ┴ ┴ ┴ ┴        */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

void	vec3_ip_add(t_vec3 *to, t_vec3 *v)
{
	to->x += v->x;
	to->y += v->y;
	to->z += v->z;
}
