/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:12:42 by tblochet          #+#    #+#             */
/*   Updated: 2024/12/11 15:20:21 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_count_flags(char const *fmt, t_formatter *fmtr)
{
	size_t	i;
	size_t	fmt_len;

	fmtr->n = 0;
	i = 0;
	fmt_len = ft_strlen(fmt);
	while (i < fmt_len)
	{
		if (fmt[i] == '%')
		{
			if (ft_char_in_s(fmt[i + 1], "cspdiuxX%"))
				fmtr->n++;
			i++;
		}
		i++;
	}
}
