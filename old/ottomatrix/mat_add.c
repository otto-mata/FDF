/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 19:31:06 by tblochet          #+#    #+#             */
/*   Updated: 2024/11/30 20:42:54 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ottomatrix.h"

t_mat	*mat_add(t_mat *mat1, t_mat *mat2)
{
	t_mat	*new_mat;
	long	sz;
	long	i;
	double	*new_values;

	if (mat1->n != mat2->n && mat1->m != mat2->m)
		return (0);
	sz = mat1->n * mat1->m;
	new_values = malloc(sz * sizeof(double));
	if (!new_values)
		return (0);
	i = 0;
	while (i < sz)
	{
		new_values[i] = mat1->values[i] + mat2->values[i];
		i++;
	}
	new_mat = mat_new(mat1->n, mat1->m, new_values);
	return (new_mat);
}
