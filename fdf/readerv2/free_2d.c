/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 22:49:39 by tblochet          #+#    #+#             */
/*   Updated: 2024/12/26 22:49:54 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readerv2.h"

void	*free_2d(void **arr2d)
{
	int	i;
	int	sz;

	sz = 0;
	i = 0;
	while (arr2d[sz])
		sz++;
	while (i < sz)
		free(arr2d[i++]);
	free(arr2d);
	return (0);
}
