/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:56:50 by tblochet          #+#    #+#             */
/*   Updated: 2024/11/15 13:31:09 by tblochet         ###   ########.fr       */
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

static void	fdf_parse_line(char *line, int lc, t_fdf_file *fdf)
{
	int			nmemb;
	int			offset;
	t_raw_data	*data;
	t_list		*lst;

	nmemb = fdf_count_points_in_raw(line);
	offset = 0;
	data = ft_calloc(1, sizeof(t_raw_data));
	if (!data)
		perror("ALLOC_ERROR");
	while (nmemb--)
	{
		data->parsed = ft_dupuntil(line + offset, ' ');
		data->len = ft_strlen(data->parsed);
		data->x = offset;
		data->y = lc;
		offset = ft_strchr(line, ' ') - line;
		lst = ft_lstnew(data);
		ft_lstadd_back(&fdf->raw_data, lst);
		data = ft_calloc(1, sizeof(t_raw_data));
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
	f->raw_data = ft_lstnew(0);
	l = get_next_line(fd);
	lc = 0;
	while (l)
	{
		fdf_parse_line(l, lc, f);
		f->width = ft_strlen(l);
		l = get_next_line(fd);
		lc++;
	}
	f->height = lc;
	return (f);
}
