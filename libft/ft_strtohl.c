/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtohl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 23:54:11 by tblochet          #+#    #+#             */
/*   Updated: 2024/12/27 00:05:57 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned long	ft_strtohl(char const *nptr)
{
	int	res;

	res = 0;
	while (*nptr == ' ' || (*nptr >= '\t' && *nptr <= '\r'))
		nptr++;
	while (*nptr && ((*nptr >= 'a' && *nptr <= 'f') || (*nptr >= 'A'
				&& *nptr <= 'F')))
	{
		res *= 16;
		res += ft_tolower(*nptr) - 'a';
		nptr++;
	}
	return (res);
}
