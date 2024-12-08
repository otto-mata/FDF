/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ottomatrix.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 19:24:50 by tblochet          #+#    #+#             */
/*   Updated: 2024/11/30 20:44:05 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OTTOMATRIX_H
# define OTTOMATRIX_H
# include <stdlib.h>

typedef struct s_mat	t_mat;

struct					s_mat
{
	int					n;
	int					m;
	double				*values;
};

t_mat					*mat_new(int n, int m, double *values);
t_mat					*mat_add(t_mat *mat1, t_mat *mat2);
t_mat					*mat_mult_mat(t_mat *mat1, t_mat *mat2);
t_mat					*mat_mult_scalar(double x, t_mat *mat);
#endif