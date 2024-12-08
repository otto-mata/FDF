/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_mult_mat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 19:42:03 by tblochet          #+#    #+#             */
/*   Updated: 2024/11/30 20:44:42 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ottomatrix.h"

static void	multiply_loop(t_mat *mat1, t_mat *mat2, double *tab)
{
	double	sum;
	long	i;
	long	j;
	long	k;

	i = 0;
	while (i < mat1->n)
	{
		j = 0;
		while (j < mat2->m)
		{
			k = 0;
			sum = 0;
			while (k < mat1->m)
			{
				sum += (mat1->values[i * mat1->m + k] * mat2->values[k * mat2->m
						+ j]);
				k++;
			}
			tab[i * mat2->m + j] = sum;
			j++;
		}
		i++;
	}
}

t_mat	*mat_mult_mat(t_mat *mat1, t_mat *mat2)
{
	double	*new_values;

	if (mat1->n != mat2->m && mat1->m != mat2->n)
		return (0);
	new_values = malloc(mat1->n * mat2->m * sizeof(double));
	if (!new_values)
		return (0);
	multiply_loop(mat1, mat2, new_values);
	return (mat_new(mat1->n, mat2->m, new_values));
}
