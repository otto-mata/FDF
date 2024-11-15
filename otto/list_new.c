/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:26:56 by tblochet          #+#    #+#             */
/*   Updated: 2024/11/15 17:33:55 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_ottolist	*list_new(void)
{
	t_ottolist	*list;

	list = ft_calloc(1, sizeof(t_ottolist));
	if (!list)
		return (0);
	list->len = 0;
	list->sz = 1;
	list->content = ft_calloc(1, sizeof(void *));
	return (list);
}