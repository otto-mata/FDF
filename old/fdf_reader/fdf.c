/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:56:50 by tblochet          #+#    #+#             */
/*   Updated: 2024/12/08 02:50:27 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*ft_dupword(char *src)
{
	char	*dest;
	size_t	src_len;
	size_t	i;

	i = 0;
	src_len = ft_strlen(src);
	dest = ft_calloc(src_len + 1, sizeof(char));
	if (!dest)
		return (0);
	while (src[i] && src[i] != ' ' && src[i] != '\n')
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}

static void	fdf_parse_line(char *line, int lc, t_ottolist **lst)
{
	int			i;
	int			x;
	t_raw_data	*data;

	i = -1;
	data = ft_calloc(1, sizeof(t_raw_data));
	if (!data)
		perror("ALLOC_ERROR");
	x = 0;
	while (line[++i] && line[i] != '\n')
	{
		if (line[i] == ' ')
			continue ;
		data->parsed = ft_dupword(&line[i]);
		data->len = ft_strlen(data->parsed);
		data->x = x;
		data->y = lc;
		i += data->len;
		list_append(data, lst);
		data = ft_calloc(1, sizeof(t_raw_data));
		x++;
	}
}

t_fdf_file	*fdf_parse_file(char const *path)
{
	int const	fd = open(path, O_RDONLY);
	t_fdf_file	*f;
	char		*l;
	int			lc;

	if (fd < 0)
		return (0);
	f = ft_calloc(1, sizeof(t_fdf_file));
	if (!f)
		return (0);
	f->raw_data = list_new();
	l = get_next_line(fd);
	lc = 0;
	while (l)
	{
		fdf_parse_line(l, lc, &f->raw_data);
		l = get_next_line(fd);
		lc++;
	}
	f->height = lc;
	return (f);
}
