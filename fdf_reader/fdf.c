/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:56:50 by tblochet          #+#    #+#             */
/*   Updated: 2024/11/15 18:22:49 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	fdf_count_points_in_raw(char *line)
{
	int	nmemb;
	int	i;

	i = 0;
	nmemb = 0;
	while (line[i])
	{
		if (line[i] != ' ' && (i == 0 || line[i - 1] == ' '))
			nmemb++;
		i++;
	}
	return (nmemb);
}

static void	fdf_parse_line(char *line, int lc, t_ottolist **lst)
{
	int			nmemb;
	int			i;
	t_raw_data	*data;

	nmemb = fdf_count_points_in_raw(line);
	i = -1;
	data = ft_calloc(1, sizeof(t_raw_data));
	if (!data)
		perror("ALLOC_ERROR");
	while (line[++i] && line[i] != '\n')
	{
		if (line[i] == ' ')
			continue ;
		data->parsed = ft_dupuntil(&line[i], ' ');
		data->len = ft_strlen(data->parsed);
		data->x = i;
		data->y = lc;
		list_append(data, lst);
		data = ft_calloc(1, sizeof(t_raw_data));
		i += data->len + 1;
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
		f->width = ft_strlen(l);
		l = get_next_line(fd);
		lc++;
	}
	f->height = lc;
	return (f);
}
