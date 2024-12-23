/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 09:38:52 by tblochet          #+#    #+#             */
/*   Updated: 2024/12/12 20:25:09 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int	main(int argc, char const *argv[])
{
	int	ret;

	// (void) argc;
	// (void) argv;
	// close(1);
	// setbuf(stdout, 0);
	ret = printf("     %d", 42);
	dprintf(2,"Return code: %d\n", ret);
	ret = ft_printf("     %d", 42);
	dprintf(2,"Return code: %d\n", ret);
	// printf("printf ?");
	return (0);
}
