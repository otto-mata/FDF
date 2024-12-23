/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:40:55 by tblochet          #+#    #+#             */
/*   Updated: 2024/11/28 12:44:25 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*iter;
	t_list	*next;

	if (!lst || !del)
		return ;
	iter = *lst;
	while (iter)
	{
		next = iter->next;
		del(iter->val);
		free(iter);
		iter = next;
	}
	*lst = 0;
}
