/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 11:01:51 by tblochet          #+#    #+#             */
/*   Updated: 2024/12/11 20:31:37 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_bzero(void *mem, size_t sz)
{
	while (sz--)
		*(unsigned char *)mem++ = 0;
}

void	*ft_calloc(size_t nmemb, size_t sz)
{
	void	*ptr;

	if (nmemb > 0 && sz > SIZE_MAX / nmemb)
		return (0);
	ptr = malloc(nmemb * sz);
	if (ptr)
		ft_bzero(ptr, nmemb * sz);
	return (ptr);
}
