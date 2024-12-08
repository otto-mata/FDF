/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:05:28 by tblochet          #+#    #+#             */
/*   Updated: 2024/11/15 17:48:12 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H
# include "../libft/libft.h"

struct s_ottolist
{
	int		sz;
	int		len;
	void	**content;
};

typedef struct s_ottolist	t_ottolist;

t_ottolist	*list_new(void);
void		*list_append(void *data, t_ottolist **list);
void		list_clear(t_ottolist **list);
void		*list_del(int idx, t_ottolist **list, void (*f)(void *m));

#endif