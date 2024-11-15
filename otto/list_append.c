/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_append.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:26:59 by tblochet          #+#    #+#             */
/*   Updated: 2024/11/15 17:44:00 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

static void	*list_expand(t_ottolist *list)
{
	t_ottolist	*cpy;
	int			idx;

	cpy = ft_calloc(1, sizeof(t_ottolist));
	if (!cpy)
		return (0);
	cpy->len = list->len;
	cpy->sz = list->sz * 2;
	cpy->content = ft_calloc(cpy->sz, sizeof(void *));
	if (!cpy->content)
		return (0);
	idx = 0;
	while (list->content[idx])
	{
		cpy->content[idx] = list->content[idx];
		idx++;
	}
	free(list);
	list = cpy;
	return (cpy);
}

void	*list_append(void *data, t_ottolist **list)
{
	if ((*list)->len + 1 > (*list)->sz / 2)
	{
		*list = list_expand(*list);
		if (!list)
			return (0);
	}
	(*list)->content[(*list)->len] = data;
	(*list)->len++;
	return (*list);
}
