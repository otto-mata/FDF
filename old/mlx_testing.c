/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_testing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 21:08:32 by tblochet          #+#    #+#             */
/*   Updated: 2024/12/08 03:54:23 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_reader/fdf.h"
#include "get_next_line.h"
#include "minilibx-linux/mlx.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	int		sz;
	t_data	img;
}			t_vars;

static t_vars g_vars;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	my_mlx_square(t_data *data, int x, int y, int sz, int color)
{
	int	i;

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

void	my_mlx_grid(t_data *data, int x, int y, int width, int height, int sz,
		int color)
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
	int	i;
	int	j;

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

void draw(int x, int y)
{
	my_mlx_pixel_put(&g_vars.img, x, y, 0xFFFFFFFF);
}

#include <math.h>

static void	plot_low_increment(int *d, int dy_dx, int *y, int yi)
{
	int	dx;
	int	dy;

	dx = dy_dx >> 16;
	dy = dy_dx & 0xFFFF;
	if (*d > 0)
	{
		*y += yi;
		*d -= (2 * dx);
	}
	*d += (2 * dy);
}

static void	plot_high_increment(int *d, int dx_dy, int *x, int xi)
{
	int	dx;
	int	dy;

	dx = dx_dy >> 16;
	dy = dx_dy & 0xFFFF;
	if (*d > 0)
	{
		*x += xi;
		*d -= (2 * dy);
	}
	*d += (2 * dx);
}

static void	plot_line_low(int x0, int y0, int x1, int y1)
{
	int	dx;
	int	dy;
	int	yi;
	int	d;
	int	x;

	dx = x1 - x0;
	dy = y1 - y0;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	else
	{
		yi = 1;
	}
	d = (2 * dy) - dx;
	x = x0;
	while (x <= x1)
	{
		draw(x, y0);
		plot_low_increment(&d, (dx << 16) | dy, &y0, yi);
		x++;
	}
}

static void	plot_line_high(int x0, int y0, int x1, int y1)
{
	int	dx;
	int	dy;
	int	xi;
	int	d;
	int	y;

	dx = x1 - x0;
	dy = y1 - y0;
	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	else
	{
		xi = 1;
	}
	d = (2 * dx) - dy;
	y = y0;
	while (y <= y1)
	{
		draw(x0, y);
		plot_high_increment(&d, (dx << 16) | dy, &x0, xi);
		y++;
	}
}

void	bresenham_line(t_point3 a, t_point3 b)
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;

	x0 = (int)round(a.x);
	y0 = (int)round(a.y);
	x1 = (int)round(b.x);
	y1 = (int)round(b.y);
	if (abs(y1 - y0) < abs(x1 - x0))
	{
		if (x0 > x1)
			plot_line_low(x1, y1, x0, y0);
		else
			plot_line_low(x0, y0, x1, y1);
	}
	else
	{
		if (y0 > y1)
			plot_line_high(x1, y1, x0, y0);
		else
			plot_line_high(x0, y0, x1, y1);
	}
}
#define WIDTH 100
#define HEIGHT 100
int	main(int argc, char *argv[])
{
	t_fdf_file *f;
	t_map3 *clean_map;
	t_ottolist *lst;
	t_point3 *point;
	t_point3 points[4];

	if (argc != 2)
		return (1);
	f = fdf_parse_file(argv[1]);
	clean_map = fdf_convert_raw_data(f);
	lst = clean_map->points;
	g_vars.mlx = mlx_init();
	g_vars.sz = 10;
	if (!g_vars.mlx)
		return (1);
	g_vars.img.img = mlx_new_image(g_vars.mlx, WIDTH, HEIGHT);
	g_vars.win = mlx_new_window(g_vars.mlx, WIDTH, HEIGHT, "Hello world!");
	g_vars.img.addr = mlx_get_data_addr(g_vars.img.img, &g_vars.img.bits_per_pixel,
			&g_vars.img.line_length, &g_vars.img.endian);
	int sz = clean_map->width >= clean_map->height ? clean_map->width : clean_map->height;
	sz = WIDTH / sz;
	// printf("cell size: %d\n", sz);
	for (int i = 0; i < lst->len; i++)
	{
		point = lst->content[i];
		point->x *= sz;
		point->y *= sz;
	}
	printf("w:%d h:%d\n",clean_map->width, clean_map->height );
	for (int i = 0; i < clean_map->width - 1; i++)
	{
		for (int k = 0; k < clean_map->height - 1; k++)
		{
			points[0] = *(t_point3 *)lst->content[k * clean_map->width + i];
			points[1] = *(t_point3 *)lst->content[k * clean_map->width + (i + 1)];
			points[2] = *(t_point3 *)lst->content[(k + 1) * clean_map->width + i + 1];
			points[3] = *(t_point3 *)lst->content[(k + 1) * clean_map->width + i];
			// printf("[%f, %f]\n", points[0].x, points[0].y);
			bresenham_line(points[0], points[1]);
			bresenham_line(points[1], points[2]);
			bresenham_line(points[2], points[3]);
			bresenham_line(points[3], points[0]);
		}

		// if ((int)(point->x) % 2 == 0)
	}
	
	// This loops over the "raw" image data (the pixel values in the image)
	// and output the values of each one
	for (size_t i = 0; i < (WIDTH + 4) * HEIGHT * 4; i += 4)
	{
		printf("%08x ", ((int)g_vars.img.addr[i]));
		if (i > 0 && i % g_vars.img.line_length == g_vars.img.line_length - 4)
			printf("\n");
	}
	
	// mlx_put_image_to_window(g_vars.mlx, g_vars.win, g_vars.img.img, 0, 0);
	// mlx_loop(g_vars.mlx);
	return (0);
}
