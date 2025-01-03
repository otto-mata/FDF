/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   ft_strtohl.c                                         ┌─┐┌┬┐┌┬┐┌─┐        */
/*                                                        │ │ │  │ │ │        */
/*   By: tblochet <tblochet@student.42.fr>                └─┘ ┴  ┴ └─┘        */
/*                                                        ┌┬┐┌─┐┌┬┐┌─┐        */
/*   Created: 2025/01/03 02:03:31 by tblochet             │││├─┤ │ ├─┤        */
/*   Updated: 2025/01/03 02:42:45 by tblochet             ┴ ┴┴ ┴ ┴ ┴ ┴        */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_utils.h"

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
