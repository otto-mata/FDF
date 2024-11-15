/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdfreader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:28:27 by tblochet          #+#    #+#             */
/*   Updated: 2024/11/15 13:33:23 by tblochet         ###   ########.fr       */
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
	t_fdf_file *f = fdf_parse_file("./test_maps/42.fdf");
	printf("%d x %d\n", f->width, f->height);
	ft_lstiter(f->raw_data, putstr_wrapper);
	return 0;
}
