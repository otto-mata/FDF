/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_mult_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 19:37:21 by tblochet          #+#    #+#             */
/*   Updated: 2024/11/30 20:44:03 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ottomatrix.h"

t_mat	*mat_mult_scalar(double x, t_mat *mat)
{
	t_mat	*new_mat;
	long	sz;
	long	i;
	double	*new_values;

	sz = mat->n * mat->m;
	new_values = malloc(sz * sizeof(int));
	if (!new_values)
		return (0);
	i = 0;
	while (i < sz)
	{
		new_values[i] = mat->values[i] * x;
		i++;
	}
	new_mat = mat_new(mat->n, mat->m, new_values);
	return (new_mat);
}
