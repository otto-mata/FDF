/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   get_file_size.c                                      ┌─┐┌┬┐┌┬┐┌─┐        */
/*                                                        │ │ │  │ │ │        */
/*   By: tblochet <tblochet@student.42.fr>                └─┘ ┴  ┴ └─┘        */
/*                                                        ┌┬┐┌─┐┌┬┐┌─┐        */
/*   Created: 2024/12/26 20:53:22 by tblochet             │││├─┤ │ ├─┤        */
/*   Updated: 2025/01/03 02:42:38 by tblochet             ┴ ┴┴ ┴ ┴ ┴ ┴        */
/*                                                                            */
/* ************************************************************************** */

#include "readerv2.h"

ssize_t	get_file_size(char const *path)
{
	ssize_t	sz;
	ssize_t	inc;
	int		fd;
	char	buf[1024];

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	if (read(fd, 0, 0) < 0)
		return (-1);
	sz = 0;
	inc = 1;
	while (inc > 0)
	{
		inc = read(fd, buf, 1024);
		if (inc > 0)
			sz += inc;
	}
	return (sz);
}
