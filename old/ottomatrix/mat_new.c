/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 19:26:40 by tblochet          #+#    #+#             */
/*   Updated: 2024/11/30 20:43:08 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ottomatrix.h"

t_mat	*mat_new(int n, int m, double *values)
{
	t_mat	*mat;

	mat = malloc(sizeof(t_mat));
	if (!mat)
		return (0);
	mat->n = n;
	mat->m = m;
	mat->values = values;
	return (mat);
}
