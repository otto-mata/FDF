/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 11:01:51 by tblochet          #+#    #+#             */
/*   Updated: 2024/12/11 20:32:57 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_memcmp(void const *m1, void const *m2, size_t sz)
{
	unsigned char const	*s1 = (const unsigned char *)m1;
	unsigned char const	*s2 = (const unsigned char *)m2;

	while (sz-- > 0)
	{
		if (*s1++ != *s2++)
		{
			if (s1[-1] < s2[-1])
				return (-1);
			return (1);
		}
	}
	return (0);
}

static size_t	ft_min(size_t a, size_t b)
{
	if (a < b)
		return (a);
	return (b);
}

static size_t	ft_max(size_t a, size_t b)
{
	if (a > b)
		return (a);
	return (b);
}

int	ft_strncmp(char const *s1, char const *s2, size_t n)
{
	n = ft_min(n, ft_max(ft_strlen(s1), ft_strlen(s2)));
	return (ft_memcmp(s1, s2, n));
}
