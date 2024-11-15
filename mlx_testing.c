/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_testing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 21:08:32 by tblochet          #+#    #+#             */
/*   Updated: 2024/11/15 19:12:48 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx-linux/mlx.h"
#include "get_next_line.h"
#include "fdf_reader/fdf.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	int		sz;
	t_data	img;
}				t_vars;


void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	my_mlx_square(t_data *data, int x, int y, int sz, int color)
{
	int		i;

	i = 0;
	while (i <= sz)
	{
		my_mlx_pixel_put(data, x + i, y, color);
		my_mlx_pixel_put(data, x, y + i, color);
		my_mlx_pixel_put(data, x + sz, y + i, color);
		my_mlx_pixel_put(data, x + i, y + sz, color);
		i++;
	}
}

void	my_mlx_grid(t_data *data, int x, int y, int width, int height, int sz, int color)
{
	int	ix;
	int	iy;

	iy = y;
	while (iy < height)
	{

		ix = x;
		while (ix < width)
		{
			my_mlx_square(data, ix, iy, sz, color);
			ix += sz;
		}
		iy += sz;
	}
}
int	my_mlx_fill_img(t_data *img, int color)
{
	int i;
	int j;

	i = 0;
	while (i < 701)
	{
		j = 0;
		while (j < 701)
		{
			my_mlx_pixel_put(img, i, j, color);
			j++;
		}
		i++;
	}
	return (0);
}

uint32_t	mlx_color_from_z(double z_value)
{
	uint32_t	base;
	uint32_t	offset;
	int			sign;

	offset = 0x05050505;
	base = 0xffffffff;
	if (z_value < 0)
	{
		z_value = -z_value;
		sign = -1;
	}
	else
		sign = 1;
	base += (offset * z_value) * sign;
	if (base > 0xffffffff)
		base = 0xffffffff;
	return (base);
}

int main(void)
{
	t_fdf_file	*f = fdf_parse_file("./test_maps/elem2.fdf");
	t_map3		*clean_map = fdf_convert_raw_data(f);
	t_ottolist	*lst = clean_map->points;
	t_point3	*point;
	t_vars		vars;

	vars.mlx = mlx_init();
	vars.sz = 10;
	if (!vars.mlx)
		return (1);
	vars.img.img = mlx_new_image(vars.mlx, 700, 700);
	vars.win = mlx_new_window(vars.mlx, 700, 700, "Hello world!");
	vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel, &vars.img.line_length,
			&vars.img.endian);
				
	for (int i = 0; i < lst->len; i++)
	{
		point = lst->content[i];
		if (point->z)
			my_mlx_square(&vars.img, point->x * 1, point->y * 2, 1, mlx_color_from_z(point->z));
	}
	// mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, 0, 0);
	mlx_loop(vars.mlx);
	return (0);
}