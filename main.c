/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 21:08:32 by tblochet          #+#    #+#             */
/*   Updated: 2024/11/14 22:51:18 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx-linux/mlx.h"
#include <stdio.h>

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_vars {
	void	*mlx;
	void	*win;
	int		sz;
	t_data	img;
	t_data	img2;
}				t_vars;

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
}