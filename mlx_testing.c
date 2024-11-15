/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 21:08:32 by tblochet          #+#    #+#             */
/*   Updated: 2024/11/15 10:45:46 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx-linux/mlx.h"
#include "get_next_line.h"
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
	t_data	img2;
}				t_vars;

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}				t_vec3;

typedef t_vec3	t_point3;

typedef struct s_map3
{
	t_point3	*points;
	int			width;
	int			height;
}				t_map3;


void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == 65451)
		vars->sz++;
	else if (keycode == 65453)
		if (vars->sz > 1)
			vars->sz--;
	printf("key event %d\n", keycode);
	return (0);
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
int	render_next_frame(t_vars *vars)
{
	// mlx_put_image_to_window(vars->mlx, vars->win, vars->img2.img, 0, 0);
	my_mlx_fill_img(&vars->img, 0);
	my_mlx_grid(&vars->img, 0, 0, 700, 700, vars->sz, 0x00FF0000);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	return (0);
}

t_point3	*ft_create_point(double x, double y, double z)
{
	t_point3	*p;

	p = calloc(1, sizeof(t_point3));
	if (!p)
		return (0);
	p->x = x;
	p->y = y;
	p->z = z;
	return (p);
}

int	ft_map3_len(t_map3 *m)
{
	int			i;
	t_point3	**p;

	i = 0;
	p = &m->points;
	while (p[i])
		i++;
	return (i);
}

int	ft_append_point_to(t_point3 *p, t_map3 *m)
{
	t_point3	*copy;
	int const	m_len = ft_map3_len(m);
	int			i;

	copy = calloc(m_len + 2, sizeof(t_point3));
	if (!copy)
		return (1);
	i = 0;
	while (i < m_len)
	{
		copy[i] = m->points[i];
		i++;
	}
	free(m->points);
	m->points = copy;
	m->points[i].x = p->x;
	m->points[i].y = p->y;
	m->points[i].z = p->z;
	free(p);
	return (0);
}

t_map3	*ft_points_from_map(char **map_lines)
{
	t_map3	*map3;
	int		x;
	int		y;
	int		z;
	int		line_len;

	map3 = calloc(1, sizeof(t_map3));
	if (!map3)
		return (0);
	map3->points = calloc(2, sizeof(t_point3));
	y = 0;
	while (map_lines[y])
	{
		x = 0;
		line_len = strlen(map_lines[y]);
		while (map_lines[y][x])
		{
			z = map_lines[y][x];
			if (isdigit(z))
				printf("p{%d, %d, %d}\n", x, y, z - '0');
				// ft_append_point_to(ft_create_point(x, y, z - 48), map3);
			x++;
		}
		y++;
	}
	map3->height = y + 1;
	map3->width = x + 1;
	return (map3);
}

int main(void)
{
	char **arr;
	int fd;

	fd = open("test_maps/42.fdf", O_RDONLY);
	arr = calloc(12, sizeof(char *));
	for (int i = 0; i < 12; i++)
	{
		arr[i] = get_next_line(fd);
	}
	
	t_map3 *m3 = ft_points_from_map((char **)arr);
	printf("map - %dx%d\n",m3->width, m3->height);
	// for (int i = 0; i < m3->height * m3->width; i++)
	// {
	// 	printf("p3[%d]{%f, %f, %f}\n",i,m3->points[i].x,m3->points[i].y,m3->points[i].z);
	// }
	
}
/*
int	main(void)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.sz = 10;
	if (!vars.mlx)
		return (1);
	vars.img.img = mlx_new_image(vars.mlx, 700, 700);
	vars.img2.img = mlx_new_image(vars.mlx, 700, 700);
	my_mlx_fill_img(&vars.img2, 0x0);
	vars.win = mlx_new_window(vars.mlx, 700, 700, "Hello world!");
	vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel, &vars.img.line_length,
			&vars.img.endian);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	mlx_loop(vars.mlx);
	return (0);
}*/