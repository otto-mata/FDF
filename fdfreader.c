/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdfreader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:28:27 by tblochet          #+#    #+#             */
/*   Updated: 2024/11/15 18:41:14 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_reader/fdf.h"

void putstr_wrapper(void *content)
{
	t_raw_data	*ctnt;

	ctnt = content;
	ft_putendl_fd(ctnt->parsed, 1);
}

int main(void)
{
	t_fdf_file	*f = fdf_parse_file("./test_maps/42.fdf");
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
