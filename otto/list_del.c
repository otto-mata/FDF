/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_del.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:26:54 by tblochet          #+#    #+#             */
/*   Updated: 2024/11/15 17:54:32 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	*list_del(int idx, t_ottolist **list, void (*fn_free)(void *m))
{
	int		i;
	void	*tmp;

	i = idx;
	fn_free((*list)->content[idx]);
	(*list)->content[idx] = 0;
	while (i < (*list)->len)
	{
		tmp = (*list)->content[i];
		(*list)->content[i] = (*list)->content[i + 1];
		(*list)->content[i + 1] = tmp;
		i++;
	}
	(*list)->len--;
	return (0);
}