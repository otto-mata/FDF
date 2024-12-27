/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_fdf_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 20:50:25 by tblochet          #+#    #+#             */
/*   Updated: 2024/12/26 23:08:23 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readerv2.h"

static bool	char_check(char c)
{
	return ((c >= '0' && c <= '9') || c == 'x' || c == ',' || (c >= 'a'
			&& c <= 'f') || (c >= 'A' && c <= 'F') || (c >= '\t' && c <= '\r')
		|| c == ' ' || c == '-');
}

static bool	check_valid_chars(char const *content)
{
	char	encounters[128];
	int		i;

	ft_bzero(&encounters, 128);
	i = -1;
	while (content[++i])
		encounters[content[i]]++;
	i = -1;
	while (++i < 128)
		if (encounters[i])
			if (!char_check(i))
				return (false);
	return (true);
}

static bool	check_constant_width(char const *content)
{
	char	**lines;
	char	**l_iter;
	int		width;
	int		i;
	bool	ok;

	lines = ft_split(content, '\n');
	if (!lines)
		return (false);
	width = 0;
	i = -1;
	ok = true;
	while (lines[++i])
	{
		l_iter = ft_split(lines[i], ' ');
		if (!l_iter)
			return (free_2d((void **)lines), false);
		if (!width)
			width = arrlen((void **)l_iter);
		else if (width != arrlen((void **)l_iter))
			ok = false;
		free_2d((void **)l_iter);
	}
	free_2d((void **)lines);
	return (ok);
}

bool	validate_fdf_file(char *file_path)
{
	const char	*file_content = get_file_content(file_path);
	bool		content_ok;
	bool		width_ok;

	if (!file_content)
		return (false);
	content_ok = check_valid_chars(file_content);
	width_ok = check_constant_width(file_content);
	free((void *)file_content);
	return (content_ok && width_ok);
}
