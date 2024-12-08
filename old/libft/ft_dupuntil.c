/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dupuntil.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:51:42 by tblochet          #+#    #+#             */
/*   Updated: 2024/11/15 13:23:33 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_dupuntil(char *src, char c)
{
	char	*dest;
	size_t	src_len;
	size_t	i;

	i = 0;
	src_len = ft_strlen(src);
	dest = ft_calloc(src_len + 1, sizeof(char));
	if (!dest)
		return (0);
	while (src[i] && src[i] != c)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}
