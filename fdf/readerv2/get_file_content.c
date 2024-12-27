/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_content.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 20:54:53 by tblochet          #+#    #+#             */
/*   Updated: 2024/12/27 12:01:18 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readerv2.h"

char	*get_file_content(char const *path)
{
	int		fd;
	ssize_t	file_size;
	char	*content;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	if (read(fd, 0, 0) < 0)
		return (0);
	file_size = get_file_size(path);
	if (file_size < 0)
		return (0);
	content = malloc((file_size + 1) * sizeof(char));
	if (!content)
		return (0);
	content[file_size] = 0;
	if (read(fd, content, file_size) < 0)
		return (free(content), (char *)0);
	return (content);
}
