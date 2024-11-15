/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:29:04 by tblochet          #+#    #+#             */
/*   Updated: 2024/11/15 17:55:01 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

int	main(void)
{
	t_ottolist	*l1;
	char		*some_data;
	char		*str;

	l1 = list_new();
	some_data = ft_strdup("Hello, World");
	list_append(some_data, &l1);
	some_data = ft_strdup("Hello, World ?");
	list_append(some_data, &l1);
	some_data = ft_strdup("toto");
	list_append(some_data, &l1);
	some_data = ft_strdup("tata");
	list_append(some_data, &l1);
	some_data = ft_strdup("tutu");
	list_append(some_data, &l1);
	list_del(0, &l1, free);
	for (int i = 0; i < l1->len; i++)
	{
		str = (char *)l1->content[i];
		printf("%s\n",str);
	}
	return (0);
}