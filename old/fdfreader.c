/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdfreader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:28:27 by tblochet          #+#    #+#             */
/*   Updated: 2024/12/07 15:22:29 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_reader/fdf.h"


int main(void)
{
	t_fdf_file	*f = fdf_parse_file("./test_maps/plat.fdf");
	t_map3		*clean_map = fdf_convert_raw_data(f);
	t_ottolist	*lst = clean_map->points;
	t_point3	*point;
	
	for (int i = 0; i < lst->len; i++)
	{
		point = lst->content[i];
		printf("p3{%f, %f, %f}\n", point->x, point->y, point->z);
	}
	
	return 0;
}
