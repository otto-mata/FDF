/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:26:57 by tblochet          #+#    #+#             */
/*   Updated: 2024/11/15 17:46:13 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	list_clear(t_ottolist **list)
{
	int	i;

	i = 0;
	while (i <= (*list)->len)
	{
		free((*list)->content[i]);
		i++;
	}
	(*list)->sz = 0;
	(*list)->len = 0;
	free(*list);
}
